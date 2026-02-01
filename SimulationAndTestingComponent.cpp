#include "SimulationAndTestingComponent.h"

#include "Math/UnrealMathUtility.h"

USimulationAndTestingComponent::USimulationAndTestingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USimulationAndTestingComponent::BeginPlay()
{
    Super::BeginPlay();

    const double StressFactor = CalculateStressFactor(AppliedForce, ElasticModulus);
    UE_LOG(LogTemp, Log, TEXT("Stress Factor (S): %.4f"), StressFactor);
}

double USimulationAndTestingComponent::CalculateStressFactor(double Force, double Modulus) const
{
    if (FMath::IsNearlyZero(Modulus))
    {
        UE_LOG(LogTemp, Error, TEXT("Elastic modulus (E) cannot be zero!"));
        return 0.0;
    }

    return Force / Modulus;
}
