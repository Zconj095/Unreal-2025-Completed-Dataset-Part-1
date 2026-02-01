#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementalInteractionComplexityIndex.generated.h"

UCLASS()
class PEKBGGAP_API AElementalInteractionComplexityIndex : public AActor
{
	GENERATED_BODY()

public:
	AElementalInteractionComplexityIndex();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateEICI() const;

public:
	UPROPERTY(EditAnywhere, Category = "EICI")
	float Beta = 2.0f;

	UPROPERTY(EditAnywhere, Category = "EICI")
	TArray<float> Concentrations = {1.2f, 0.8f, 1.5f};

	UPROPERTY(EditAnywhere, Category = "EICI")
	TArray<float> InteractionPathwayLengths = {3.0f, 2.0f, 4.5f};
};
