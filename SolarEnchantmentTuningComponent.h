#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <complex>
#include "SolarEnchantmentTuningComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USolarEnchantmentTuningComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USolarEnchantmentTuningComponent();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    using Complex = std::complex<double>;

    UPROPERTY(EditAnywhere, Category="Enchantment")
    TArray<float> Amplitudes;

    UPROPERTY(EditAnywhere, Category="Enchantment")
    TArray<float> Frequencies;

    UPROPERTY(EditAnywhere, Category="Enchantment")
    TArray<float> PhaseAlignments;

    UPROPERTY(EditAnywhere, Category="Enchantment")
    int32 HarmonicCount = 5;

    void ValidateParameters() const;
    Complex CalculateSolarEnchantmentEnergy(float Time) const;
};
