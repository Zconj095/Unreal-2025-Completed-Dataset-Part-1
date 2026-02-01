#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HybridAdaptationRateComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UHybridAdaptationRateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHybridAdaptationRateComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hybrid Adaptation Rate", meta = (AllowPrivateAccess = "true", ToolTip = "A0: Initial adaptability"))
	float InitialAdaptability = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hybrid Adaptation Rate", meta = (AllowPrivateAccess = "true", ToolTip = "λ: Rate of adaptation decay"))
	float DecayRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hybrid Adaptation Rate", meta = (AllowPrivateAccess = "true", ToolTip = "∇Φ: Magical energy enhancing adaptation"))
	float EnergyGradient = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hybrid Adaptation Rate", meta = (AllowPrivateAccess = "true", ToolTip = "Time step increment"))
	float TimeStep = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hybrid Adaptation Rate", meta = (AllowPrivateAccess = "true", ToolTip = "Total number of time steps"))
	int32 TotalSteps = 100;

	UPROPERTY(EditAnywhere, Category = "Hybrid Adaptation Rate", meta = (ToolTip = "Draw debug spheres for the adaptation curve"))
	bool bDrawDebugGizmos = true;

	TArray<float> AdaptationCurve;

	void CalculateAdaptationCurve();
	void LogAdaptationCurve() const;
	void TensorFlowValidation() const;
	void DrawAdaptationGizmos() const;

public:
	UFUNCTION(BlueprintCallable, Category = "Hybrid Adaptation Rate")
	void RecalculateAdaptation();

	UFUNCTION(BlueprintCallable, Category = "Hybrid Adaptation Rate")
	const TArray<float>& GetAdaptationCurve() const;
};
