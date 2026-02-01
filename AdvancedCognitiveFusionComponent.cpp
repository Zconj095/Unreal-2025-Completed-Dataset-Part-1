// Converted from Unity MonoBehaviour AdvancedCognitiveFusionSimulator to Unreal ActorComponent.
#include "AdvancedCognitiveFusionComponent.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInterface.h"
#include "Math/UnrealMathUtility.h"

UAdvancedCognitiveFusionComponent::UAdvancedCognitiveFusionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UAdvancedCognitiveFusionComponent::BeginPlay()
{
    Super::BeginPlay();
    EnsureVisualRepresentation();
    SimulateFusion();
    UpdateVisualRepresentation();
}

void UAdvancedCognitiveFusionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    SimulateFusion();
    UpdateVisualRepresentation();
}

void UAdvancedCognitiveFusionComponent::SimulateFusion()
{
    FVector AccumulatedVector = FVector::ZeroVector;
    float TotalIntensity = 0.0f;
    FLinearColor BlendedColor = FLinearColor::Black;

    for (const FCognitiveState& State : CognitiveStates)
    {
        const float Intensity = FMath::Clamp(State.Intensity, 0.0f, 1.0f);
        AccumulatedVector += State.EmotionVector * Intensity;
        TotalIntensity += Intensity;
        BlendedColor += State.StateColor * Intensity;
    }

    if (TotalIntensity > SMALL_NUMBER)
    {
        AccumulatedVector /= TotalIntensity;
        BlendedColor /= TotalIntensity;
    }

    const float NormalizedIntensity = (CognitiveStates.Num() > 0) ? FMath::Clamp(TotalIntensity / CognitiveStates.Num(), 0.0f, 1.0f) : 0.0f;

    FusedCognitiveState.FusedVector = AccumulatedVector;
    FusedCognitiveState.OverallIntensity = NormalizedIntensity;
    FusedCognitiveState.BlendedColor = BlendedColor;
}

void UAdvancedCognitiveFusionComponent::EnsureVisualRepresentation()
{
    if (VisualRepresentation && VisualRepresentation->IsValidLowLevel())
    {
        return;
    }

    if (AActor* Owner = GetOwner())
    {
        if (!Owner->GetRootComponent())
        {
            USceneComponent* Root = NewObject<USceneComponent>(Owner, TEXT("FusionRoot"));
            Root->RegisterComponent();
            Owner->SetRootComponent(Root);
        }

        VisualRepresentation = NewObject<UStaticMeshComponent>(Owner, TEXT("CognitiveFusionSphere"));
        if (VisualRepresentation)
        {
            VisualRepresentation->SetupAttachment(Owner->GetRootComponent());
            VisualRepresentation->RegisterComponent();

            static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
            if (SphereMesh.Succeeded())
            {
                VisualRepresentation->SetStaticMesh(SphereMesh.Object);
            }

            DynamicMaterial = VisualRepresentation->CreateDynamicMaterialInstance(0);
        }
    }
}

void UAdvancedCognitiveFusionComponent::UpdateVisualRepresentation()
{
    if (!VisualRepresentation)
    {
        return;
    }

    const FVector NewLocation = FusedCognitiveState.FusedVector;
    const FVector NewScale = FVector::OneVector * FMath::Max(0.1f, FusedCognitiveState.OverallIntensity * 2.0f);

    VisualRepresentation->SetWorldLocation(NewLocation);
    VisualRepresentation->SetWorldScale3D(NewScale);

    if (DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue(TEXT("Color"), FusedCognitiveState.BlendedColor);
    }
    else
    {
        const FVector ColorVector(FusedCognitiveState.BlendedColor.R, FusedCognitiveState.BlendedColor.G, FusedCognitiveState.BlendedColor.B);
        VisualRepresentation->SetVectorParameterValueOnMaterials(TEXT("Color"), ColorVector);
    }
}
