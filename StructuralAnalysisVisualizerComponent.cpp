#include "StructuralAnalysisVisualizerComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Math/UnrealMathUtility.h"

UStructuralAnalysisVisualizerComponent::UStructuralAnalysisVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStructuralAnalysisVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!StressIndicatorClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("StressIndicatorClass must be assigned."));
        return;
    }

    for (float Force = ForceStart; Force <= ForceEnd; Force += ForceStep)
    {
        for (float Area = AreaStart; Area <= AreaEnd; Area += AreaStep)
        {
            const double Stress = CalculateStress(Force, Area);
            SpawnIndicator(Force, Stress, Area);
        }
    }
}

double UStructuralAnalysisVisualizerComponent::CalculateStress(double Force, double Area) const
{
    if (FMath::IsNearlyZero(Area))
    {
        return 0.0;
    }
    return Force / Area;
}

void UStructuralAnalysisVisualizerComponent::SpawnIndicator(float Force, double Stress, float Area) const
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    const FVector Location = FVector(Force / 500.0f, Stress * HeightScale, Area / 10.0f);
    const FTransform Transform(FRotator::ZeroRotator, Location, FVector::OneVector);
    AActor* Indicator = World->SpawnActor<AActor>(StressIndicatorClass, Transform);
    if (!Indicator)
    {
        return;
    }

    const float ScaleMultiplier = StressScaleFactor * static_cast<float>(Stress);
    Indicator->SetActorScale3D(FVector(ScaleMultiplier));

    if (UStaticMeshComponent* Mesh = Indicator->FindComponentByClass<UStaticMeshComponent>())
    {
        UMaterialInstanceDynamic* DynamicMaterial = Mesh->CreateAndSetMaterialInstanceDynamic(0);
        if (DynamicMaterial)
        {
            DynamicMaterial->SetVectorParameterValue(TEXT("BaseColor"), StressColor(Stress));
        }
    }
}

FLinearColor UStructuralAnalysisVisualizerComponent::StressColor(double Stress) const
{
    const float T = FMath::Clamp(static_cast<float>(Stress) / 100.0f, 0.0f, 1.0f);
    return FLinearColor::LerpUsingHSV(FLinearColor::Green, FLinearColor::Red, T);
}
