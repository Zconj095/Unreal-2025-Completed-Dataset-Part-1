#include "FluxSignalGeneratorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

UFluxSignalGeneratorComponent::UFluxSignalGeneratorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    bAutoActivate = true;
}

void UFluxSignalGeneratorComponent::BeginPlay()
{
    Super::BeginPlay();

    EnsureHyperfluxArrays();

    if (bRandomizeOnBeginPlay)
    {
        // Randomize initial phases for hyperflux
        for (int32 i = 0; i < Phases.Num(); ++i)
        {
            Phases[i] = FMath::FRandRange(0.0f, 2.0f * PI);
        }
        // Slightly vary mono phase
        MonoPhase += FMath::FRandRange(0.0f, 0.5f * PI);
    }
}

void UFluxSignalGeneratorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!IsActive()) { return; }

    const float Time = bUseWorldTime && GetWorld() ? GetWorld()->TimeSeconds : AccumulatedTime;

    // Fixed-rate sampling (accumulate and step at SampleRate)
    const float StepInterval = SampleRate > 0.0f ? (1.0f / SampleRate) : DeltaTime;
    SampleAccumulator += DeltaTime;
    while (SampleAccumulator >= StepInterval)
    {
        const float Dt = StepInterval;
        const float T = bUseWorldTime && GetWorld() ? GetWorld()->TimeSeconds : (AccumulatedTime + Dt);

        switch (Mode)
        {
        case EFluxMode::Monoflux:
            StepMonoflux(T, Dt);
            break;
        case EFluxMode::Hyperflux:
            StepHyperflux(T, Dt);
            break;
        default:
            break;
        }

        SampleAccumulator -= StepInterval;
        AccumulatedTime += Dt;
    }

    if (bDrawDebug)
    {
        if (AActor* Owner = GetOwner())
        {
            const FVector Loc = Owner->GetActorLocation();
            const FVector Up = Owner->GetActorUpVector();
            const float Mag = FMath::Clamp(CurrentValue, -1.0f, 1.0f) * DebugScale;
            DrawDebugLine(GetWorld(), Loc, Loc + Up * Mag, DebugColor, false, 0.0f, 0, 2.0f);
        }
    }
}

void UFluxSignalGeneratorComponent::EnsureHyperfluxArrays()
{
    const int32 N = FMath::Max(1, NumChannels);
    if (ChannelFrequencies.Num() != N) { ChannelFrequencies.SetNum(N); }
    if (ChannelAmplitudes.Num() != N) { ChannelAmplitudes.SetNum(N); }
    if (PhaseVelocities.Num()   != N) { PhaseVelocities.SetNum(N); }
    if (Phases.Num()            != N) { Phases.SetNum(N); }
    if (CurrentChannels.Num()   != N) { CurrentChannels.SetNum(N); }

    // Initialize defaults if zeros
    for (int32 i = 0; i < N; ++i)
    {
        if (ChannelFrequencies[i] <= 0.0f)
        {
            ChannelFrequencies[i] = 110.0f + 20.0f * i; // simple spread
        }
        if (ChannelAmplitudes[i] == 0.0f)
        {
            ChannelAmplitudes[i] = 1.0f / N; // normalized by default
        }
        if (PhaseVelocities[i] == 0.0f)
        {
            PhaseVelocities[i] = 0.2f + 0.03f * i; // slow drift
        }
    }
}

void UFluxSignalGeneratorComponent::StepMonoflux(float Time, float Dt)
{
    // Coherent single-channel with small band-limited wobble (low entropy)
    const float Coherent = MonoAmplitude * FMath::Sin(2.0f * PI * MonoFrequency * Time + MonoPhase);
    const float Wobble = MonoEntropy * FMath::PerlinNoise1D(Time * 0.25f) * MonoAmplitude;
    CurrentChannels.SetNum(1);
    CurrentChannels[0] = Coherent + Wobble;

    CurrentValue = CurrentChannels[0];
    if (bNormalizeOutput)
    {
        CurrentValue = FMath::Clamp(CurrentValue, -1.0f, 1.0f);
    }

    OnFluxSample.Broadcast(CurrentValue, CurrentChannels);
}

void UFluxSignalGeneratorComponent::StepHyperflux(float Time, float Dt)
{
    EnsureHyperfluxArrays();

    const int32 N = CurrentChannels.Num();
    if (N <= 0) { CurrentValue = 0.0f; return; }

    // Update phases with Kuramoto-like coupling and chaos term
    for (int32 i = 0; i < N; ++i)
    {
        float CouplingSum = 0.0f;
        for (int32 k = 0; k < N; ++k)
        {
            if (k == i) { continue; }
            CouplingSum += FMath::Sin(Phases[k] - Phases[i]);
        }
        const float CouplingTerm = (N > 1) ? (CouplingStrength * CouplingSum / (float)(N - 1)) : 0.0f;
        const float ChaosNoise = ChaosFactor * FMath::PerlinNoise1D(Time * 0.5f + i * 31.317f);
        const float DTheta = PhaseVelocities[i] + CouplingTerm + ChaosNoise;
        Phases[i] = FMath::Fmod(Phases[i] + DTheta * Dt, 2.0f * PI);
        if (Phases[i] < 0.0f) { Phases[i] += 2.0f * PI; }
    }

    float Sum = 0.0f;
    for (int32 i = 0; i < N; ++i)
    {
        const float S = ChannelAmplitudes[i] * FMath::Sin(2.0f * PI * ChannelFrequencies[i] * Time + Phases[i]);
        CurrentChannels[i] = S;
        Sum += S;
    }

    CurrentValue = Sum;
    if (bNormalizeOutput)
    {
        // Simple soft normalization to [-1,1] using tanh-like clamp
        CurrentValue = FMath::Clamp(CurrentValue, -1.0f, 1.0f);
    }

    OnFluxSample.Broadcast(CurrentValue, CurrentChannels);
}

