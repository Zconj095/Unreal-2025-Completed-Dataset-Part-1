// Minimal, focused Unreal Engine translation of the provided Python analyzer.
// Exposes Blueprint-callable methods and data structures for use in UE projects.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BrainwaveAnalysisLibrary.h"
#include "EnhancedBrainwaveAnalyzer.generated.h"

// Use FChakraData from BrainwaveAnalysisLibrary.h

USTRUCT(BlueprintType)
struct FFrequencyRange
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double Min = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double Max = 0.0;
};

// Use FQuantumMetrics from BrainwaveAnalysisLibrary.h

// Use FDNAResonance from BrainwaveAnalysisLibrary.h

// Use FWavelengthMetrics from BrainwaveAnalysisLibrary.h

// Use FChakraAnalysis from BrainwaveAnalysisLibrary.h

// Use FChakraSystemMetrics from BrainwaveAnalysisLibrary.h

USTRUCT(BlueprintType)
struct FChakraSystemAnalysis
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FName, FChakraAnalysis> IndividualChakras;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FChakraSystemMetrics SystemMetrics;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Recommendations;
};

USTRUCT(BlueprintType)
struct FComprehensiveAnalysisResults
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<double> Frequencies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<double> Wavelengths;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FWavelengthMetrics> Metrics;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuantumMetrics> QuantumData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FDNAResonance> DNAResonance;
};

USTRUCT(BlueprintType)
struct FSummaryStatistics
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 TotalAnalyzed = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double FreqMin = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double FreqMax = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double FreqMean = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double FreqStd = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double WaveMin = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double WaveMax = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double WaveMean = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double WaveStd = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, int32> BandDistribution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, double> BandPercentages;
};

USTRUCT(BlueprintType)
struct FComprehensiveAnalysis
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FComprehensiveAnalysisResults AnalysisResults;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FSummaryStatistics SummaryStatistics;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double MinFrequency = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    double MaxFrequency = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NumFrequencies = 0;
};

UCLASS(BlueprintType)
class PEKBGGAP_API UEnhancedBrainwaveAnalyzer : public UObject
{
    GENERATED_BODY()

public:
    UEnhancedBrainwaveAnalyzer();

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    FQuantumMetrics CalculateQuantumCoherence(double Frequency, double Amplitude = 1.0) const;

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    FDNAResonance CalculateDNAResonance(double Frequency, double DNAFreq = 1.0e8) const;

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    FString ClassifyFrequency(double Frequency) const;

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    FWavelengthMetrics CalculateWavelengthMetrics(double PulseFrequency, double PulseAmplitude = 0.0001, double MagneticFieldDirection = 1.0) const;

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    FChakraSystemAnalysis AnalyzeChakraSystem(const TArray<double>& OptionalFrequencies);

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    void GenerateFrequencyRange(double MinFreq, double MaxFreq, int32 NumFrequencies, TArray<double>& OutFrequencies) const;

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    FComprehensiveAnalysis GenerateComprehensiveFrequencyAnalysis(double MinFreq = 0.5, double MaxFreq = 2000.0, int32 NumFrequencies = 5000);

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    bool ExportComprehensiveData(const FComprehensiveAnalysis& ComprehensiveResults, const FChakraSystemAnalysis& ChakraResults, const FString& Filename) const;

    UFUNCTION(BlueprintCallable, Category = "Brainwave")
    FChakraAnalysis EnhancedChakraAnalysis(FName ChakraName);

private:
    double SpeedOfLight = 299792458.0;
    int32 MaxFrequencies = 10000;

    TMap<FName, FChakraData> Chakras;
    TArray<FName> ChakraOrder;

    TMap<FString, FFrequencyRange> FrequencyRanges;
    TMap<FString, TArray<FString>> CorticalAssociations;
    TMap<FString, TArray<FString>> ActivityAssociations;

    TArray<FString> GenerateRecommendations(const TMap<FName, FChakraAnalysis>& Analyses) const;
    static void ComputeBasicStats(const TArray<double>& Data, double& OutMin, double& OutMax, double& OutMean, double& OutStd);
};
