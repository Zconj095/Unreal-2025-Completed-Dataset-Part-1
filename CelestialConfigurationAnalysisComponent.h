#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CelestialConfigurationAnalysisComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UCelestialConfigurationAnalysisComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCelestialConfigurationAnalysisComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Configuration")
	float SemiMajorAxis = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Configuration")
	float Eccentricity = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Configuration")
	float OrbitalAngle = PI / 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Configuration")
	float AngularVelocity = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Celestial Configuration")
	float TimeSeconds = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Celestial Configuration")
	float Distance = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Celestial Configuration")
	float CalculateCelestialPosition(float SemiMajor, float EccentricityValue, float Angle, float Omega, float TimeValue) const;
};
