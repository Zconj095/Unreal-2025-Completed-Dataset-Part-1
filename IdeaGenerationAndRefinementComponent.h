#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IdeaGenerationAndRefinementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UIdeaGenerationAndRefinementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UIdeaGenerationAndRefinementComponent();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idea Generation", meta = (AllowPrivateAccess = "true", ToolTip = "Number of connections formed between ideas"))
	float Connections = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Idea Generation", meta = (AllowPrivateAccess = "true", ToolTip = "Logical constraints imposed on the design"))
	float Constraints = 10.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Idea Generation", meta = (AllowPrivateAccess = "true"))
	float CreativePotential = 0.0f;

	void InitializeParameters();
	float CalculateCreativePotential(float InConnections, float InConstraints) const;
	float PredictCreativePotentialWithMockNetwork(float InConnections, float InConstraints) const;
	float ComputeCreativePotentialWithTensorFlowStub(float InConnections, float InConstraints) const;
	void LogCreativePotential(float InCreativePotential) const;

public:
	UFUNCTION(BlueprintCallable, Category = "Idea Generation")
	void RecalculateCreativePotential();

	UFUNCTION(BlueprintCallable, Category = "Idea Generation")
	float GetCreativePotential() const { return CreativePotential; }
};
