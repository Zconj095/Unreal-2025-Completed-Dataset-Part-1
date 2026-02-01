#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SylvanicGlandComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USylvanicGlandComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USylvanicGlandComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Sylvanic Gland")
    float ReleaseRate = 10.0f;

    UPROPERTY(EditAnywhere, Category="Sylvanic Gland")
    float ManaDecayRate = 0.1f;

    UPROPERTY(EditAnywhere, Category="Sylvanic Gland")
    float SimulationTime = 10.0f;

    UPROPERTY(EditAnywhere, Category="Sylvanic Gland")
    float TimeStep = 0.1f;

    float ElapsedTime = 0.0f;
    float ManaPotency = 0.0f;

    void SimulateManaOutput(float DeltaTime);
    float CalculateManaPotency(float Time) const;
};
