// Converted from Unity MonoBehaviour CognitiveFusionSimulator to Unreal ActorComponent.
#include "CognitiveFusionComponent.h"
#include "GameFramework/Actor.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

UCognitiveFusionComponent::UCognitiveFusionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCognitiveFusionComponent::BeginPlay()
{
    Super::BeginPlay();
    EnsureVisualRepresentation();
    SimulateFusion();
    UpdateVisualRepresentation();
}

void UCognitiveFusionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    SimulateFusion();
    UpdateVisualRepresentation();
}

void UCognitiveFusionComponent::SimulateFusion()
{
    float TotalIntensity = 0.0f;
    FLinearColor BlendedColor = FLinearColor::Black;

    for (const FCognitiveStateEntry& State : CognitiveStates)
    {
        const float Intensity = FMath::Clamp(State.Intensity, 0.0f, 1.0f);
        TotalIntensity += Intensity;
        BlendedColor += State.StateColor * Intensity;
    }

    if (CognitiveStates.Num() > 0)
    {
        BlendedColor /= CognitiveStates.Num();
    }

    FusedCognitiveState.FusedName = TEXT("Fused Emotion State");
    FusedCognitiveState.CombinedIntensity = (CognitiveStates.Num() > 0)
        ? FMath::Clamp(TotalIntensity / CognitiveStates.Num(), 0.0f, 1.0f)
        : 0.0f;
    FusedCognitiveState.BlendedColor = BlendedColor;
}

void UCognitiveFusionComponent::EnsureVisualRepresentation()
{
    if (VisualRepresentation && VisualRepresentation->IsValidLowLevel())
    {
        return;
    }

    if (AActor* Owner = GetOwner())
    {
        if (!Owner->GetRootComponent())
        {
            USceneComponent* Root = NewObject<USceneComponent>(Owner, TEXT("CognitiveFusionRoot"));
            Root->RegisterComponent();
            Owner->SetRootComponent(Root);
        }

        VisualRepresentation = NewObject<UStaticMeshComponent>(Owner, TEXT("CognitiveFusionSphere"));
        if (VisualRepresentation)
        {
            VisualRepresentation->SetupAttachment(Owner->GetRootComponent());
            VisualRepresentation->RegisterComponent();
            ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
            if (SphereMesh.Succeeded())
            {
                VisualRepresentation->SetStaticMesh(SphereMesh.Object);
            }

            DynamicMaterial = VisualRepresentation->CreateDynamicMaterialInstance(0);
        }
    }
}

void UCognitiveFusionComponent::UpdateVisualRepresentation()
{
    if (!VisualRepresentation)
    {
        return;
    }

    const FVector NewScale = FVector::OneVector * FMath::Max(0.1f, FusedCognitiveState.CombinedIntensity * 2.0f);
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
