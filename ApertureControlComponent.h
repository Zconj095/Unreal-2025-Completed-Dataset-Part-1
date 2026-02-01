// Converted from Unity MonoBehaviour to an Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ApertureControlComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UApertureControlComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UApertureControlComponent();

    /** Radius of the aperture opening. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aperture")
    float ApertureRadius = 0.5f;

    /** Intensity factor based on aperture size. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Aperture")
    float IntensityFactor = 1.0f;

    /** Calculate the beam intensity based on the current aperture radius. */
    UFUNCTION(BlueprintCallable, Category="Aperture")
    float CalculateIntensity(float BeamRadius) const;

protected:
    virtual void BeginPlay() override;

#if WITH_EDITOR
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#endif
};
