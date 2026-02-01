// Converted from Unity MonoBehaviour to Unreal ActorComponent.
#include "CognitionStateSynergizerComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

#include "Engine/StaticMeshActor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "InputCoreTypes.h"
#include "TimerManager.h"

UCognitionStateSynergizerComponent::UCognitionStateSynergizerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UCognitionStateSynergizerComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeExampleStates();
    SynergizeStates();
}

void UCognitionStateSynergizerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (GetWorld() && GetWorld()->GetFirstPlayerController())
    {
        if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::S))
        {
            SynergizeStates();
        }
    }
}

void UCognitionStateSynergizerComponent::InitializeExampleStates()
{
    if (CognitiveStates.Num() == 0)
    {
        CognitiveStates.Add({TEXT("Focus"), 0.8f, FLinearColor::Blue});
        CognitiveStates.Add({TEXT("Memory"), 0.6f, FLinearColor::Green});
        CognitiveStates.Add({TEXT("Emotion"), 0.4f, FLinearColor::Red});
    }
}

void UCognitionStateSynergizerComponent::SynergizeStates()
{
    if (CognitiveStates.Num() == 0)
    {
        return;
    }

    float TotalIntensity = 0.0f;
    FLinearColor BlendedColor = FLinearColor::Black;

    for (const FCoreCognitiveState& State : CognitiveStates)
    {
        const float Intensity = FMath::Clamp(State.Intensity, 0.0f, 1.0f);
        TotalIntensity += Intensity;
        BlendedColor += State.StateColor * Intensity;
    }

    SynergizedIntensity = FMath::Clamp(TotalIntensity / CognitiveStates.Num(), 0.0f, 1.0f);
    if (TotalIntensity > SMALL_NUMBER)
    {
        SynergizedColor = BlendedColor / TotalIntensity;
    }
    else
    {
        SynergizedColor = FLinearColor::Black;
    }

    UE_LOG(LogTemp, Log, TEXT("Synergized Intensity: %.3f"), SynergizedIntensity);
    UE_LOG(LogTemp, Log, TEXT("Synergized Color: %s"), *SynergizedColor.ToString());

    UpdateVisualization();
}

void UCognitionStateSynergizerComponent::UpdateVisualization()
{
    SpawnVisualizationSphere();
}

void UCognitionStateSynergizerComponent::SpawnVisualizationSphere()
{
    if (!GetWorld())
    {
        return;
    }

    AStaticMeshActor* SphereActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector(0,0,100), FRotator::ZeroRotator);
    if (!SphereActor)
    {
        return;
    }

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        SphereActor->GetStaticMeshComponent()->SetStaticMesh(SphereMesh.Object);
    }

    SphereActor->SetActorScale3D(FVector::OneVector * SynergizedIntensity * 2.0f);
    SphereActor->SetActorEnableCollision(false);

    UMaterialInstanceDynamic* DynamicMaterial = SphereActor->GetStaticMeshComponent()->CreateDynamicMaterialInstance(0);
    if (DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue(TEXT("Color"), SynergizedColor);
    }
    else
    {
        const FVector ColorVector(SynergizedColor.R, SynergizedColor.G, SynergizedColor.B);
        SphereActor->GetStaticMeshComponent()->SetVectorParameterValueOnMaterials(TEXT("Color"), ColorVector);
    }

    TWeakObjectPtr<AStaticMeshActor> WeakSphere = SphereActor;
    FTimerHandle DestroyTimer;
    GetWorld()->GetTimerManager().SetTimer(
        DestroyTimer,
        FTimerDelegate::CreateLambda([WeakSphere]()
        {
            if (WeakSphere.IsValid())
            {
                WeakSphere->Destroy();
            }
        }),
        1.0f,
        false);
}
