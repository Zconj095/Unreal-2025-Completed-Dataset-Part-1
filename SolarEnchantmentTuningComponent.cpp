#include "SolarEnchantmentTuningComponent.h"
#include "Engine/World.h"

#include "Math/UnrealMathUtility.h"
#include <complex>

using Complex = std::complex<double>;

USolarEnchantmentTuningComponent::USolarEnchantmentTuningComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarEnchantmentTuningComponent::BeginPlay()
{
    Super::BeginPlay();
    ValidateParameters();
}

void USolarEnchantmentTuningComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const float TimeValue = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    const Complex TotalEnergy = CalculateSolarEnchantmentEnergy(TimeValue);
    const double Magnitude = std::abs(TotalEnergy);

    UE_LOG(LogTemp, Log, TEXT("E_solar magnitude: %.4f, real: %.4f, imag: %.4f"),
        Magnitude, TotalEnergy.real(), TotalEnergy.imag());
}

void USolarEnchantmentTuningComponent::ValidateParameters() const
{
    if (Amplitudes.Num() != HarmonicCount ||
        Frequencies.Num() != HarmonicCount ||
        PhaseAlignments.Num() != HarmonicCount)
    {
        UE_LOG(LogTemp, Error, TEXT("Ensure arrays match harmonic count."));
    }
}

Complex USolarEnchantmentTuningComponent::CalculateSolarEnchantmentEnergy(float Time) const
{
    Complex TotalEnergy(0.0, 0.0);

    const int32 Count = FMath::Clamp(HarmonicCount, 1, Amplitudes.Num());
    for (int32 Index = 0; Index < Count; ++Index)
    {
        const double AngularFrequency = 2.0 * PI * static_cast<double>(Frequencies.IsValidIndex(Index) ? Frequencies[Index] : 0.0f);
        const double Phase = PhaseAlignments.IsValidIndex(Index) ? PhaseAlignments[Index] : 0.0f;
        const double Amplitude = Amplitudes.IsValidIndex(Index) ? Amplitudes[Index] : 0.0f;

        const double Argument = AngularFrequency * static_cast<double>(Time) + Phase;
        Complex Harmonic = Complex(std::cos(Argument), std::sin(Argument)) * Amplitude;
        TotalEnergy += Harmonic;
    }

    return TotalEnergy;
}
