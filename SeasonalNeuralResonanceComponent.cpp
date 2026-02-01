#include "SeasonalNeuralResonanceComponent.h"

#include "Math/UnrealMathUtility.h"

USeasonalNeuralResonanceComponent::USeasonalNeuralResonanceComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    Amplitudes.Init(1.0f, 4);
    Frequencies.Init(1.0f / 365.0f, 4);
    PhaseShifts.Init(0.0f, 4);
}

void USeasonalNeuralResonanceComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USeasonalNeuralResonanceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UpdateResonance(DeltaTime);
}

void USeasonalNeuralResonanceComponent::UpdateResonance(float DeltaTime)
{
    TimeElapsed += DeltaTime;
    const double PsiSeasonal = CalculateSeasonalNeuralResonance(TimeElapsed);
    UE_LOG(LogTemp, Log, TEXT("Ψ_seasonal(t) at t=%.2f s: %.4f"), TimeElapsed, PsiSeasonal);
}

double USeasonalNeuralResonanceComponent::CalculateSeasonalNeuralResonance(float Time) const
{
    int32 ComponentCount = Amplitudes.Num();
    ComponentCount = FMath::Min(ComponentCount, Frequencies.Num());
    ComponentCount = FMath::Min(ComponentCount, PhaseShifts.Num());

    if (ComponentCount <= 0)
    {
        return 0.0;
    }

    double SeasonalResonance = 0.0;
    for (int32 Index = 0; Index < ComponentCount; ++Index)
    {
        const double CycleComponent = 2.0 * PI * Frequencies[Index] * Time + PhaseShifts[Index];
        SeasonalResonance += static_cast<double>(Amplitudes[Index]) * FMath::Cos(CycleComponent);
    }

    return SeasonalResonance;
}
