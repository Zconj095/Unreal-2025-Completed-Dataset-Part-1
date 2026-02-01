#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialNeuralResonanceComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialNeuralResonanceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialNeuralResonanceComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Resonance")
	int32 SourcesCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Resonance")
	TArray<float> EnergyAmplitudes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Resonance")
	TArray<float> Frequencies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Resonance")
	TArray<float> PhaseShifts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Resonance")
	float ResonanceValue = 0.0f;
};
