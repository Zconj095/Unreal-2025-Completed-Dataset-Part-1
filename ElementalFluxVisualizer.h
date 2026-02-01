#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementalFluxVisualizer.generated.h"

UCLASS()
class PEKBGGAP_API AElementalFluxVisualizer : public AActor
{
	GENERATED_BODY()

public:
	AElementalFluxVisualizer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Flux")
	TSubclassOf<AActor> FluxPointClass;

	UPROPERTY(EditAnywhere, Category = "Flux", meta = (ClampMin = "0.01"))
	float DivergenceScale = 0.01f;

	UPROPERTY(EditAnywhere, Category = "Flux", meta = (ClampMin = "0.0"))
	float MagicDecay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Flux", meta = (ClampMin = "1"))
	int32 PointsPerAxis = 2;

	UPROPERTY(EditAnywhere, Category = "Flux", meta = (ClampMin = "100"))
	float GridSpacing = 200.0f;
};
