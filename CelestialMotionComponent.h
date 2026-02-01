#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialMotionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialMotionComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Orbital")
	float SemiMajorAxis = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Orbital")
	float Eccentricity = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Orbital", meta = (ClampMin = "3"))
	int32 NumPoints = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Orbital")
	TArray<FVector> OrbitPoints;

	UFUNCTION(BlueprintCallable, Category = "Celestial Orbital")
	float CalculateOrbitalDistance(float Theta, float SemiMajor, float EccentricityValue) const;
};
