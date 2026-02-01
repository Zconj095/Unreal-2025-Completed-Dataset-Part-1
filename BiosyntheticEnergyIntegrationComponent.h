#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BiosyntheticEnergyIntegrationComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBiosyntheticEnergyIntegrationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBiosyntheticEnergyIntegrationComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biosynthetic Energy")
	float FreeEnergyChange = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biosynthetic Energy")
	float StartTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biosynthetic Energy")
	float EndTime = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biosynthetic Energy", meta = (ClampMin = "1"))
	int32 IntegrationSteps = 1000;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Biosynthetic Energy")
	float IntegratedEnergy = 0.0f;

	UFUNCTION(BlueprintCallable, Category = "Biosynthetic Energy")
	float EnergyFlux(float TimeSeconds) const;

	UFUNCTION(BlueprintCallable, Category = "Biosynthetic Energy")
	float CalculateBiosyntheticEnergy() const;
};
