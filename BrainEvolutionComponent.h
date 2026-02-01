#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrainEvolutionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBrainEvolutionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBrainEvolutionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain Evolution")
	int32 NumNodes = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain Evolution")
	int32 FeatureSize = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain Evolution")
	TArray<float> AdjacencyMatrix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain Evolution")
	TArray<float> InitialFeatures;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain Evolution")
	TArray<float> WeightMatrix1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain Evolution")
	TArray<float> WeightMatrix2;

	UFUNCTION(BlueprintCallable, Category = "Brain Evolution")
	TArray<float> ComputeGNN() const;
};
