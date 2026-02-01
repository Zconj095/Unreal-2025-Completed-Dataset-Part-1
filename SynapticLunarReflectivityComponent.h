#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SynapticLunarReflectivityComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USynapticLunarReflectivityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USynapticLunarReflectivityComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(EditAnywhere, Category="Reflectivity")
    float BaseReflectivity = 1.0f;

    UPROPERTY(EditAnywhere, Category="Reflectivity")
    float LunarSensitivity = 0.5f;

    UPROPERTY(EditAnywhere, Category="Reflectivity")
    float AngularFrequency = 1.0f;

    UPROPERTY(EditAnywhere, Category="Reflectivity")
    float PhaseOffset = 0.0f;

    float CurrentTime = 0.0f;
    float LunarReflectivity = 0.0f;

    float CalculateLunarReflectivity(float Time) const;
};
