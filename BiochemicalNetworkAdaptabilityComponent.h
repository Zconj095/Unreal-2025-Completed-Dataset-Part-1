#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiochemicalNetworkAdaptabilityComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiochemicalNetworkAdaptabilityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiochemicalNetworkAdaptabilityComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/** λ: Fantasy constant for adaptability. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Network")
	float Lambda = 1.0f;

	/** ΔN_bio: Node change measure. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Network")
	float DeltaNetwork = 10.0f;

	/** Δt: Time period (seconds). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biochemical Network")
	float DeltaTime = 1.0f;

	/** Cached BNA result. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biochemical Network")
	float NetworkAdaptability = 0.0f;

	/** Calculates BNA = λ * (ΔN_bio / Δt). */
	UFUNCTION(BlueprintCallable, Category = "Biochemical Network")
	float CalculateBNA(float LambdaValue, float DeltaNetworkValue, float DeltaTimeValue) const;
};
