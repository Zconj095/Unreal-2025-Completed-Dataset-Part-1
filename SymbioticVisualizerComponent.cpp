#include "SymbioticVisualizerComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

USymbioticVisualizerComponent::USymbioticVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USymbioticVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();

    const double Benefit = CalculateBenefit();
    UE_LOG(LogTemp, Log, TEXT("Total Symbiotic Benefit: %.2f"), Benefit);

    VisualizeResources();
}

void USymbioticVisualizerComponent::VisualizeResources()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Origin = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;

    if (Species1ActorClass)
    {
        const FVector Location = Origin + FVector(0.0f, Resource1, 0.0f);
        AActor* Actor = World->SpawnActor<AActor>(Species1ActorClass, Location, FRotator::ZeroRotator);
        if (Actor)
        {
            Actor->SetActorScale3D(FVector(1.0f, Resource1 / 10.0f, 1.0f));
        }
    }
    if (Species2ActorClass)
    {
        const FVector Location = Origin + FVector(100.0f, Resource2, 0.0f);
        AActor* Actor = World->SpawnActor<AActor>(Species2ActorClass, Location, FRotator::ZeroRotator);
        if (Actor)
        {
            Actor->SetActorScale3D(FVector(1.0f, Resource2 / 10.0f, 1.0f));
        }
    }
}

double USymbioticVisualizerComponent::CalculateBenefit() const
{
    if (EfficiencyConstant <= 0.0f || Resource1 <= 0.0f || Resource2 <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Symbiotic parameters must be positive."));
        return 0.0;
    }

    return EfficiencyConstant * Resource1 * Resource2;
}
