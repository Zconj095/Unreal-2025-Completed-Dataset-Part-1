#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructuralStabilityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStructuralStabilityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStructuralStabilityComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Stability")
    float Force = 1000.0f;

    UPROPERTY(EditAnywhere, Category="Stability")
    float Area = 50.0f;

    void EvaluateStress() const;
    float CalculateStress(float ForceValue, float AreaValue) const;
};
