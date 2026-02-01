#include "BrainwaveLiveAnalyzerComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

namespace
{
    FORCEINLINE void BandRange(EBrainwaveBand Band, double& OutMin, double& OutMax)
    {
        switch (Band)
        {
        case EBrainwaveBand::Delta: OutMin = 0.5; OutMax = 4.0; break;
        case EBrainwaveBand::Theta: OutMin = 4.0; OutMax = 8.0; break;
        case EBrainwaveBand::Alpha: OutMin = 8.0; OutMax = 13.0; break;
        case EBrainwaveBand::Beta:  OutMin = 13.0; OutMax = 30.0; break;
        case EBrainwaveBand::Gamma: OutMin = 30.0; OutMax = 100.0; break;
        default: OutMin = 0.5; OutMax = 4.0; break;
        }
    }

    FORCEINLINE FLinearColor BandColor(EBrainwaveBand Band)
    {
        switch (Band)
        {
        case EBrainwaveBand::Delta: return FLinearColor(0.204f, 0.596f, 0.859f); // #3498db
        case EBrainwaveBand::Theta: return FLinearColor(0.180f, 0.800f, 0.443f); // #2ecc71
        case EBrainwaveBand::Alpha: return FLinearColor(0.953f, 0.612f, 0.071f); // #f39c12
        case EBrainwaveBand::Beta:  return FLinearColor(0.905f, 0.298f, 0.235f); // #e74c3c
        case EBrainwaveBand::Gamma: return FLinearColor(0.608f, 0.349f, 0.714f); // #9b59b6
        default: return FLinearColor::White;
        }
    }
}

UBrainwaveLiveAnalyzerComponent::UBrainwaveLiveAnalyzerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    // Initialize containers and locks
    const TArray<EBrainwaveBand> Bands = { EBrainwaveBand::Delta, EBrainwaveBand::Theta, EBrainwaveBand::Alpha, EBrainwaveBand::Beta, EBrainwaveBand::Gamma };
    for (EBrainwaveBand B : Bands)
    {
        LiveData.Add(B, FLiveBandData{});
        Locks.Add(B, new FCriticalSection());
    }
}

void UBrainwaveLiveAnalyzerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBrainwaveLiveAnalyzerComponent::StartLiveAnalysis(float DurationSeconds)
{
    if (!GetWorld() || bIsRunning)
    {
        return;
    }

    // Reset state
    for (auto& Pair : LiveData)
    {
        Pair.Value.Timestamps.Reset();
        Pair.Value.Frequencies.Reset();
        Pair.Value.Wavelengths.Reset();
        Pair.Value.Amplitudes.Reset();
    }
    UpdateCount = 0;
    StartSeconds = FPlatformTime::Seconds();
    bIsRunning = true;

    const float Interval = 1.0f / FMath::Max(1.0f, UpdateRateHz);
    GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &UBrainwaveLiveAnalyzerComponent::UpdateSimulation, Interval, true);

    if (DurationSeconds > 0.0f)
    {
        GetWorld()->GetTimerManager().SetTimer(StopTimer, FTimerDelegate::CreateUObject(this, &UBrainwaveLiveAnalyzerComponent::StopLiveAnalysis), DurationSeconds, false);
    }
}

void UBrainwaveLiveAnalyzerComponent::StopLiveAnalysis()
{
    if (!GetWorld()) return;
    GetWorld()->GetTimerManager().ClearTimer(UpdateTimer);
    GetWorld()->GetTimerManager().ClearTimer(StopTimer);
    bIsRunning = false;
}

void UBrainwaveLiveAnalyzerComponent::UpdateSimulation()
{
    const double Now = FPlatformTime::Seconds() - StartSeconds;

    for (const auto& Pair : LiveData)
    {
        const EBrainwaveBand Band = Pair.Key;
        double MinF, MaxF; BandRange(Band, MinF, MaxF);
        const double BaseFreq = (MinF + MaxF) * 0.5;
        const double Variation = (MaxF - MinF) * 0.3;
        const double Noise = FMath::FRandRange(-Variation, Variation);
        const double Frequency = FMath::Clamp(BaseFreq + Noise + FMath::Sin(Now * 0.5) * Variation * 0.2, MinF, MaxF - 0.1);

        const double Wavelength = (Frequency > 0.0) ? (SpeedOfLight / Frequency) : 0.0;
        double Amplitude = 0.5 + 0.3 * FMath::Sin(Now * 1.5 + (int32)Band % 10) + 0.1 * FMath::FRandRange(-1.0, 1.0);
        Amplitude = FMath::Max(0.1, Amplitude);

        PushSample(Band, Now, Frequency, Wavelength, Amplitude);
    }

    ++UpdateCount;
}

void UBrainwaveLiveAnalyzerComponent::PushSample(EBrainwaveBand Band, double Timestamp, double Frequency, double Wavelength, double Amplitude)
{
    if (FCriticalSection* CS = Locks.FindRef(Band))
    {
        FScopeLock Guard(CS);
        FLiveBandData& D = LiveData.FindChecked(Band);
        D.Timestamps.Add(Timestamp);
        D.Frequencies.Add(Frequency);
        D.Wavelengths.Add(Wavelength);
        D.Amplitudes.Add(Amplitude);

        ClampCircular(D.Timestamps, MaxSamplesPerBand);
        ClampCircular(D.Frequencies, MaxSamplesPerBand);
        ClampCircular(D.Wavelengths, MaxSamplesPerBand);
        ClampCircular(D.Amplitudes, MaxSamplesPerBand);
    }
}

void UBrainwaveLiveAnalyzerComponent::ClampCircular(TArray<double>& Arr, int32 MaxLen)
{
    if (Arr.Num() > MaxLen)
    {
        const int32 RemoveCount = Arr.Num() - MaxLen;
        Arr.RemoveAt(0, RemoveCount, EAllowShrinking::No);
    }
}

bool UBrainwaveLiveAnalyzerComponent::GetBandDataSafe(EBrainwaveBand Band, FLiveBandData& OutData) const
{
    if (FCriticalSection* CS = Locks.FindRef(Band))
    {
        FScopeLock Guard(CS);
        const FLiveBandData* D = LiveData.Find(Band);
        if (!D || D->Frequencies.Num() < 2) return false;
        const int32 MinLen = FMath::Min(
            FMath::Min(D->Timestamps.Num(), D->Frequencies.Num()),
            FMath::Min(D->Wavelengths.Num(), D->Amplitudes.Num())
        );
        if (MinLen <= 0) return false;

        const int32 StartIdx = D->Timestamps.Num() - MinLen;
        OutData.Timestamps.Reset(MinLen);
        OutData.Frequencies.Reset(MinLen);
        OutData.Wavelengths.Reset(MinLen);
        OutData.Amplitudes.Reset(MinLen);
        OutData.Timestamps.Append(D->Timestamps.GetData() + StartIdx, MinLen);
        OutData.Frequencies.Append(D->Frequencies.GetData() + (D->Frequencies.Num() - MinLen), MinLen);
        OutData.Wavelengths.Append(D->Wavelengths.GetData() + (D->Wavelengths.Num() - MinLen), MinLen);
        OutData.Amplitudes.Append(D->Amplitudes.GetData() + (D->Amplitudes.Num() - MinLen), MinLen);
        return true;
    }
    return false;
}

void UBrainwaveLiveAnalyzerComponent::ComputeAverages(const TArray<double>& In, double& OutMean)
{
    if (In.Num() == 0) { OutMean = 0.0; return; }
    long double Sum = 0.0L;
    for (double V : In) Sum += V;
    OutMean = static_cast<double>(Sum / static_cast<long double>(In.Num()));
}

bool UBrainwaveLiveAnalyzerComponent::GetBandSummary(EBrainwaveBand Band, FLiveBandSummary& OutSummary) const
{
    FLiveBandData Data;
    if (!GetBandDataSafe(Band, Data)) return false;

    OutSummary.TotalSamples = Data.Frequencies.Num();
    OutSummary.CurrentFrequency = Data.Frequencies.Last();
    OutSummary.CurrentWavelength = Data.Wavelengths.Last();
    OutSummary.CurrentAmplitude = Data.Amplitudes.Last();

    double MinF = Data.Frequencies[0];
    double MaxF = Data.Frequencies[0];
    for (double V : Data.Frequencies)
    {
        MinF = FMath::Min(MinF, V);
        MaxF = FMath::Max(MaxF, V);
    }
    OutSummary.MinFrequency = MinF;
    OutSummary.MaxFrequency = MaxF;

    ComputeAverages(Data.Frequencies, OutSummary.AverageFrequency);
    ComputeAverages(Data.Amplitudes, OutSummary.AverageAmplitude);
    return true;
}

TArray<EBrainwaveBand> UBrainwaveLiveAnalyzerComponent::GetAllBands() const
{
    return { EBrainwaveBand::Delta, EBrainwaveBand::Theta, EBrainwaveBand::Alpha, EBrainwaveBand::Beta, EBrainwaveBand::Gamma };
}

FLinearColor UBrainwaveLiveAnalyzerComponent::GetBandColor(EBrainwaveBand Band) const
{
    return BandColor(Band);
}

double UBrainwaveLiveAnalyzerComponent::GetFPS() const
{
    const double Elapsed = FPlatformTime::Seconds() - StartSeconds;
    return (Elapsed > 0.0 && bIsRunning) ? static_cast<double>(UpdateCount) / Elapsed : 0.0;
}
