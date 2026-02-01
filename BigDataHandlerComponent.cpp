// Converted from Unity MonoBehaviour BigDataHandlerSystem to Unreal ActorComponent.
#include "BigDataHandlerComponent.h"

#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "QuantumHypervectorManagerComponent.h"

UBigDataHandlerComponent::UBigDataHandlerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UBigDataHandlerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!QuantumManager)
    {
        if (UWorld* World = GetWorld())
        {
            for (TActorIterator<AActor> It(World); It; ++It)
            {
                if (UQuantumHypervectorManagerComponent* FoundManager = It->FindComponentByClass<UQuantumHypervectorManagerComponent>())
                {
                    QuantumManager = FoundManager;
                    break;
                }
            }
        }
    }

    if (!QuantumManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("BigDataHandlerComponent: QuantumHypervectorManagerComponent not found in scene."));
        return;
    }

    ActivateFoliage();
}

void UBigDataHandlerComponent::ActivateFoliage()
{
    if (!QuantumManager)
    {
        return;
    }

    const TMap<int32, FQuadrantVectorCollection>& Quadrants = QuantumManager->GetQuadrantClassification();
    for (const auto& Quadrant : Quadrants)
    {
        UE_LOG(
            LogTemp,
            Log,
            TEXT("Activating Quadrant %d with %d vectors."),
            Quadrant.Key,
            Quadrant.Value.Vectors.Num());
    }

    if (AActor* Owner = GetOwner())
    {
        const float Scale = FMath::FRandRange(0.5f, 1.5f);
        Owner->SetActorScale3D(FVector(Scale));
    }
}
