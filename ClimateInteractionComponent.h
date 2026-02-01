// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClimateInteractionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UClimateInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UClimateInteractionComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Climate")
	float AverageTemperature = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Climate")
	float Amplitude = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Climate", meta=(ClampMin="0.1"))
	float SpatialPeriod = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Climate", meta=(ClampMin="0.1"))
	float TemporalPeriod = 365.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Climate")
	float Location = 250.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Climate")
	float Temperature = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Climate")
	float CalculateTemperatureAtTime(float TimeDays) const;

private:
	float AccumulatedDays = 0.0f;
};
