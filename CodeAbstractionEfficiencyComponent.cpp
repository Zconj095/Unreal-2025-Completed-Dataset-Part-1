#include "CodeAbstractionEfficiencyComponent.h"

UCodeAbstractionEfficiencyComponent::UCodeAbstractionEfficiencyComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCodeAbstractionEfficiencyComponent::BeginPlay()
{
	Super::BeginPlay();
	CAE = (NeuronsTotal > 0) ? Beta * (NeuronsAbstract / NeuronsTotal) : 0.0f;
}

void UCodeAbstractionEfficiencyComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (NeuronsTotal <= 0.0f)
	{
		UE_LOG(LogTemp, Error, TEXT("N_total must be greater than zero."));
		CAE = 0.0f;
		return;
	}

	CAE = Beta * (NeuronsAbstract / NeuronsTotal);
	UE_LOG(LogTemp, Log, TEXT("Code Abstraction Efficiency (CAE): %.4f"), CAE);
}

void UCodeAbstractionEfficiencyComponent::UpdateBeta(float NewBeta)
{
	Beta = NewBeta;
}

void UCodeAbstractionEfficiencyComponent::UpdateNeuronsAbstract(float NewNeurons)
{
	NeuronsAbstract = NewNeurons;
}

void UCodeAbstractionEfficiencyComponent::UpdateNeuronsTotal(float NewTotal)
{
	if (NewTotal > 0.0f)
	{
		NeuronsTotal = NewTotal;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("N_total must remain greater than zero."));
	}
}
