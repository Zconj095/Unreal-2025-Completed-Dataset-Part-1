#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EcosystemVisualizer.generated.h"

UCLASS()
class PEKBGGAP_API AEcosystemVisualizer : public AActor
{
	GENERATED_BODY()

public:
	AEcosystemVisualizer();

protected:
	virtual void BeginPlay() override;

private:
	float CalculateStability() const;

public:
	UPROPERTY(EditAnywhere, Category = "Ecosystem")
	TSubclassOf<AActor> SpeciesClass;

	UPROPERTY(EditAnywhere, Category = "Ecosystem", meta = (ClampMin = "1.0"))
	float SpeciesRichness = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Ecosystem")
	float InteractionStrength = 0.7f;

	UPROPERTY(EditAnywhere, Category = "Ecosystem")
	float Alpha = 1.2f;

	UPROPERTY(EditAnywhere, Category = "Ecosystem")
	float Beta = 0.8f;

	UPROPERTY(EditAnywhere, Category = "Ecosystem", meta = (ClampMin = "1"))
	int32 GridColumns = 10;

	UPROPERTY(EditAnywhere, Category = "Ecosystem")
	float GridSpacing = 200.0f;
};
