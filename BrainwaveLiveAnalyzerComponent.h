#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BrainwaveLiveAnalyzerComponent.generated.h"

UENUM(BlueprintType)
enum class EBrainwaveBand : uint8
{
    Delta UMETA(DisplayName = "Delta"),
    Theta UMETA(DisplayName = "Theta"),
    Alpha UMETA(DisplayName = "Alpha"),
    Beta  UMETA(DisplayName = "Beta"),
    Gamma UMETA(DisplayName = "Gamma")
};

USTRUCT(BlueprintType)
struct FLiveBandData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<double> Timestamps;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<double> Frequencies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<double> Wavelengths;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<double> Amplitudes;
};

USTRUCT(BlueprintType)
struct FLiveBandSummary
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalSamples = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double MinFrequency = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double MaxFrequency = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double CurrentFrequency = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double CurrentWavelength = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double CurrentAmplitude = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double AverageFrequency = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double AverageAmplitude = 0.0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UBrainwaveLiveAnalyzerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBrainwaveLiveAnalyzerComponent();

    UFUNCTION(BlueprintCallable, Category = "Brainwave|Live")
    void StartLiveAnalysis(float DurationSeconds = 0.0f);

    UFUNCTION(BlueprintCallable, Category = "Brainwave|Live")
    void StopLiveAnalysis();

    UFUNCTION(BlueprintCallable, Category = "Brainwave|Live")
    bool GetBandDataSafe(EBrainwaveBand Band, FLiveBandData& OutData) const;

    UFUNCTION(BlueprintCallable, Category = "Brainwave|Live")
    bool GetBandSummary(EBrainwaveBand Band, FLiveBandSummary& OutSummary) const;

    UFUNCTION(BlueprintPure, Category = "Brainwave|Live")
    TArray<EBrainwaveBand> GetAllBands() const;

    UFUNCTION(BlueprintPure, Category = "Brainwave|Live")
    FLinearColor GetBandColor(EBrainwaveBand Band) const;

    UFUNCTION(BlueprintPure, Category = "Brainwave|Live")
    bool IsRunning() const { return bIsRunning; }

    UFUNCTION(BlueprintPure, Category = "Brainwave|Live")
    double GetFPS() const;

protected:
    virtual void BeginPlay() override;

private:
    void UpdateSimulation();
    void PushSample(EBrainwaveBand Band, double Timestamp, double Frequency, double Wavelength, double Amplitude);
    static void ClampCircular(TArray<double>& Arr, int32 MaxLen);
    static void ComputeAverages(const TArray<double>& In, double& OutMean);

private:
    UPROPERTY(EditAnywhere, Category = "Brainwave|Config")
    bool bSingleWindowMode = true;

    UPROPERTY(EditAnywhere, Category = "Brainwave|Config", meta=(ClampMin="1", ClampMax="2000"))
    int32 MaxSamplesPerBand = 1000;

    UPROPERTY(EditAnywhere, Category = "Brainwave|Config", meta=(ClampMin="1.0", ClampMax="240.0"))
    float UpdateRateHz = 20.0f;

    UPROPERTY(EditAnywhere, Category = "Brainwave|Config")
    double SpeedOfLight = 299792458.0;

    TMap<EBrainwaveBand, FLiveBandData> LiveData;
    TMap<EBrainwaveBand, FCriticalSection*> Locks;

    FTimerHandle UpdateTimer;
    FTimerHandle StopTimer;
    bool bIsRunning = false;
    uint64 UpdateCount = 0;
    double StartSeconds = 0.0;
};

