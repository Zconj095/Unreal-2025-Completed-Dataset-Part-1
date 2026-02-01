#include "BiosyntheticEnergyIntegrationComponent.h"
#include "Logging/LogMacros.h"
#include "Math/UnrealMathUtility.h"

UBiosyntheticEnergyIntegrationComponent::UBiosyntheticEnergyIntegrationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBiosyntheticEnergyIntegrationComponent::BeginPlay()
{
	Super::BeginPlay();
	IntegratedEnergy = CalculateBiosyntheticEnergy();
	UE_LOG(LogTemp, Log, TEXT("Biosynthetic Energy Integration (E_b): %0.4f"), IntegratedEnergy);
}

float UBiosyntheticEnergyIntegrationComponent::EnergyFlux(float TimeSeconds) const
{
	return FMath::Sin(TimeSeconds) + 1.5f;
}

float UBiosyntheticEnergyIntegrationComponent::CalculateBiosyntheticEnergy() const
{
	const float Dt = (EndTime - StartTime) / FMath::Max(IntegrationSteps, 1);
	float Sum = 0.0f;

	for (int32 Step = 0; Step < IntegrationSteps; ++Step)
	{
		const float CurrentTime = StartTime + Step * Dt;
		Sum += FreeEnergyChange * EnergyFlux(CurrentTime) * Dt;
	}

	return Sum;
}
