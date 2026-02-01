#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StrainVisualizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStrainVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStrainVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Strain")
    float Stress = 500.0f;

    UPROPERTY(EditAnywhere, Category="Strain")
    float YoungsModulus = 200000.0f;

    UPROPERTY(EditAnywhere, Category="Strain")
    AActor* MaterialObject = nullptr;

    void ApplyStrain();
    float CalculateStrain(float StressValue, float Youngs) const;
};
