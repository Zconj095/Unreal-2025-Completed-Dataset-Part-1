#include "EnhancedBrainwaveAnalyzer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

namespace
{
    template<typename T>
    int32 ArgMin(const TArray<T>& Values)
    {
        if (Values.Num() == 0) return INDEX_NONE;
        int32 BestIdx = 0;
        T BestVal = Values[0];
        for (int32 i = 1; i < Values.Num(); ++i)
        {
            if (Values[i] < BestVal)
            {
                BestVal = Values[i];
                BestIdx = i;
            }
        }
        return BestIdx;
    }
}

UEnhancedBrainwaveAnalyzer::UEnhancedBrainwaveAnalyzer()
{
    Chakras.Add("Root", FChakraData{TEXT("Root"), 35.0, TEXT("#FF0000"), TEXT("Earth"), TEXT("Base of spine"), {TEXT("Grounding"), TEXT("Survival"), TEXT("Stability"), TEXT("Security")}});
    Chakras.Add("Sacral", FChakraData{TEXT("Sacral"), 150.0, TEXT("#FF8800"), TEXT("Water"), TEXT("Lower abdomen"), {TEXT("Creativity"), TEXT("Sexuality"), TEXT("Emotion"), TEXT("Pleasure")}});
    Chakras.Add("Solar_Plexus", FChakraData{TEXT("Solar Plexus"), 350.0, TEXT("#FFFF00"), TEXT("Fire"), TEXT("Upper abdomen"), {TEXT("Personal power"), TEXT("Confidence"), TEXT("Will"), TEXT("Transformation")}});
    Chakras.Add("Heart", FChakraData{TEXT("Heart"), 550.0, TEXT("#00FF00"), TEXT("Air"), TEXT("Center of chest"), {TEXT("Love"), TEXT("Compassion"), TEXT("Connection"), TEXT("Healing")}});
    Chakras.Add("Throat", FChakraData{TEXT("Throat"), 750.0, TEXT("#0088FF"), TEXT("Sound"), TEXT("Throat"), {TEXT("Communication"), TEXT("Truth"), TEXT("Expression"), TEXT("Clarity")}});
    Chakras.Add("Third_Eye", FChakraData{TEXT("Third Eye"), 950.0, TEXT("#4400FF"), TEXT("Light"), TEXT("Forehead"), {TEXT("Intuition"), TEXT("Wisdom"), TEXT("Vision"), TEXT("Insight")}});
    Chakras.Add("Crown", FChakraData{TEXT("Crown"), 1150.0, TEXT("#8800FF"), TEXT("Thought"), TEXT("Top of head"), {TEXT("Spirituality"), TEXT("Connection to divine"), TEXT("Enlightenment"), TEXT("Unity")}});

    ChakraOrder = {"Root", "Sacral", "Solar_Plexus", "Heart", "Throat", "Third_Eye", "Crown"};

    FrequencyRanges.Add("Delta", FFrequencyRange{0.5, 4.0});
    FrequencyRanges.Add("Theta", FFrequencyRange{4.0, 8.0});
    FrequencyRanges.Add("Alpha", FFrequencyRange{8.0, 13.0});
    FrequencyRanges.Add("Beta", FFrequencyRange{13.0, 30.0});
    FrequencyRanges.Add("Gamma", FFrequencyRange{30.0, 100.0});
    FrequencyRanges.Add("High_Gamma", FFrequencyRange{100.0, 200.0});
    FrequencyRanges.Add("Ultra_Gamma", FFrequencyRange{200.0, 1000.0});
    FrequencyRanges.Add("Hyper_Gamma", FFrequencyRange{1000.0, 5000.0});

    CorticalAssociations.Add("Alpha", {TEXT("Occipital Lobe"), TEXT("Parietal Lobe")});
    CorticalAssociations.Add("Beta", {TEXT("Frontal Lobe"), TEXT("Temporal Lobe")});
    CorticalAssociations.Add("Theta", {TEXT("Temporal Lobe"), TEXT("Parietal Lobe"), TEXT("Hippocampus")});
    CorticalAssociations.Add("Delta", {TEXT("Frontal Lobe"), TEXT("Occipital Lobe"), TEXT("Thalamus")});
    CorticalAssociations.Add("Gamma", {TEXT("All Lobes"), TEXT("Thalamo-cortical circuits")});
    CorticalAssociations.Add("High_Gamma", {TEXT("Prefrontal Cortex"), TEXT("Superior Temporal Gyrus")});
    CorticalAssociations.Add("Ultra_Gamma", {TEXT("Thalamus"), TEXT("Brainstem"), TEXT("Cerebral Cortex")});
    CorticalAssociations.Add("Hyper_Gamma", {TEXT("Quantum neural networks"), TEXT("Microtubules"), TEXT("Consciousness networks")});

    ActivityAssociations.Add("Alpha", {TEXT("Relaxation"), TEXT("Reduced anxiety"), TEXT("Creativity"), TEXT("Wakeful rest")});
    ActivityAssociations.Add("Beta", {TEXT("Alertness"), TEXT("Concentration"), TEXT("Problem-solving"), TEXT("Active thinking")});
    ActivityAssociations.Add("Theta", {TEXT("Deep relaxation"), TEXT("Daydreaming"), TEXT("Meditation"), TEXT("Memory consolidation")});
    ActivityAssociations.Add("Delta", {TEXT("Deep sleep"), TEXT("Unconsciousness"), TEXT("Healing"), TEXT("Regeneration")});
    ActivityAssociations.Add("Gamma", {TEXT("Enhanced sensory processing"), TEXT("Information binding"), TEXT("Consciousness")});
    ActivityAssociations.Add("High_Gamma", {TEXT("Advanced cognitive processing"), TEXT("Heightened awareness")});
    ActivityAssociations.Add("Ultra_Gamma", {TEXT("Hyper-synchronization"), TEXT("Global neural binding"), TEXT("Peak cognitive performance")});
    ActivityAssociations.Add("Hyper_Gamma", {TEXT("Transcendent consciousness"), TEXT("Unity experiences"), TEXT("Non-local awareness")});
}

FQuantumMetrics UEnhancedBrainwaveAnalyzer::CalculateQuantumCoherence(double Frequency, double Amplitude) const
{
    const double Planck = 6.62607015e-34;
    const double Energy = Planck * Frequency;
    FQuantumMetrics Out;
    Out.EnergyJoules = Energy;
    const double kB = 1.381e-23;
    const double T = 310.0;
    const double Den = (kB * T);
    Out.CoherenceFactor = Den > 0.0 ? FMath::Exp(-(Energy / Den)) : 0.0;
    Out.DecoherenceTimeSeconds = (Frequency > 0.0) ? 1.0 / (2.0 * PI * Frequency) : 0.0;
    const double PhaseRaw = 2.0 * PI * Frequency * Amplitude;
    Out.QuantumPhase = FMath::Fmod(PhaseRaw, 2.0 * PI);
    Out.QuantumNumber = (Den == 0.0) ? 0 : static_cast<int64>(Energy / Planck);
    Out.TemperatureKelvin = (1.381e-23 > 0.0) ? Energy / 1.381e-23 : 0.0;
    return Out;
}

FDNAResonance UEnhancedBrainwaveAnalyzer::CalculateDNAResonance(double Frequency, double DNAFreq) const
{
    FDNAResonance Out;
    Out.BaseFrequency = Frequency;
    Out.Harmonics.Reserve(10);
    Out.ResonanceRatios.Reserve(10);
    for (int32 i = 0; i < 10; ++i)
    {
        const double Harm = Frequency * static_cast<double>(i + 1);
        Out.Harmonics.Add(Harm);
        Out.ResonanceRatios.Add((Harm > 0.0) ? (DNAFreq / Harm) : 0.0);
    }

    TArray<double> FitErrors; FitErrors.Reserve(Out.ResonanceRatios.Num());
    for (double Ratio : Out.ResonanceRatios)
    {
        const double Rnd = FMath::RoundToDouble(Ratio);
        FitErrors.Add(FMath::Abs(Ratio - Rnd));
    }
    const int32 BestIdx = ArgMin(FitErrors);
    Out.OptimalHarmonic = (BestIdx != INDEX_NONE) ? Out.Harmonics[BestIdx] : 0.0;

    const double DNAWavelength = 3.4e-9;
    Out.DNAWavelengthMeters = DNAWavelength;
    const double EMWavelength = (Frequency > 0.0) ? SpeedOfLight / Frequency : 0.0;
    Out.EMWavelengthMeters = EMWavelength;

    Out.InterferenceRatio = (DNAWavelength > 0.0) ? (EMWavelength / DNAWavelength) : 0.0;
    Out.StandingWaveNodes = (Out.InterferenceRatio > 0.0) ? static_cast<int32>(Out.InterferenceRatio / 2.0) : 0;

    if (BestIdx != INDEX_NONE)
    {
        const double Ratio = Out.ResonanceRatios[BestIdx];
        const double Rnd = FMath::RoundToDouble(Ratio);
        Out.ResonanceStrength = 1.0 / (1.0 + FMath::Abs(Ratio - Rnd));
    }
    else
    {
        Out.ResonanceStrength = 0.0;
    }

    return Out;
}

FString UEnhancedBrainwaveAnalyzer::ClassifyFrequency(double Frequency) const
{
    for (const auto& KVP : FrequencyRanges)
    {
        const FFrequencyRange& R = KVP.Value;
        if (Frequency >= R.Min && Frequency < R.Max)
        {
            return KVP.Key;
        }
    }
    return TEXT("Unknown");
}

FWavelengthMetrics UEnhancedBrainwaveAnalyzer::CalculateWavelengthMetrics(double PulseFrequency, double PulseAmplitude, double MagneticFieldDirection) const
{
    FWavelengthMetrics M;
    M.PulseAmplitude = PulseAmplitude;
    M.PulseFrequency = PulseFrequency;
    M.MagneticFieldDirection = MagneticFieldDirection;
    M.Wavelength = (PulseFrequency > 0.0) ? (SpeedOfLight / PulseFrequency) : 0.0;

    M.WavelengthClass = ClassifyFrequency(PulseFrequency);
    M.Quantum = CalculateQuantumCoherence(PulseFrequency, PulseAmplitude);
    M.DNA = CalculateDNAResonance(PulseFrequency);

    const FFrequencyRange* Range = FrequencyRanges.Find(M.WavelengthClass);
    if (Range)
    {
        M.FrequencyRange = FVector2D(Range->Min, Range->Max);
    }

    if (const TArray<FString>* Regions = CorticalAssociations.Find(M.WavelengthClass))
    {
        M.CorticalRegions = *Regions;
    }
    else
    {
        M.CorticalRegions = {TEXT("Unknown")};
    }

    if (const TArray<FString>* Acts = ActivityAssociations.Find(M.WavelengthClass))
    {
        M.AssociatedActivities = *Acts;
    }
    else
    {
        M.AssociatedActivities = {TEXT("Unknown")};
    }

    if (M.Wavelength <= 100.0)
    {
        M.WavelengthCategory = TEXT("High Frequency (Low Wavelength)");
    }
    else if (M.Wavelength <= 1000.0)
    {
        M.WavelengthCategory = TEXT("Medium Frequency (Medium Wavelength)");
    }
    else
    {
        M.WavelengthCategory = TEXT("Low Frequency (High Wavelength)");
    }

    if (PulseAmplitude < 0.3)
    {
        M.WavelengthPattern = TEXT("Low Amplitude (Stable)");
    }
    else if (PulseAmplitude < 0.7)
    {
        M.WavelengthPattern = TEXT("Medium Amplitude (Variable)");
    }
    else
    {
        M.WavelengthPattern = TEXT("High Amplitude (Dynamic)");
    }

    M.PowerEstimate = PulseAmplitude * PulseAmplitude;
    M.EnergyDensity = (M.Wavelength != 0.0) ? (M.PowerEstimate / M.Wavelength) : 0.0;

    return M;
}

TArray<FString> UEnhancedBrainwaveAnalyzer::GenerateRecommendations(const TMap<FName, FChakraAnalysis>& Analyses) const
{
    TArray<FString> Recs;
    for (const auto& Pair : Analyses)
    {
        const FName ChakraName = Pair.Key;
        const FChakraAnalysis& A = Pair.Value;
        const double Activation = A.ActivationScore;
        const FString ElementLower = A.Chakra.Element.ToLower();
        if (Activation < 0.3)
        {
            Recs.Add(FString::Printf(TEXT("Consider %s element practices for %s chakra"), *ElementLower, *ChakraName.ToString()));
            if (A.Chakra.Properties.Num() > 0)
            {
                Recs.Add(FString::Printf(TEXT("Focus on %s exercises"), *A.Chakra.Properties[0].ToLower()));
            }
        }
        else if (Activation > 0.8)
        {
            Recs.Add(FString::Printf(TEXT("%s chakra is highly active - maintain balance"), *ChakraName.ToString()));
        }
    }
    return Recs;
}

void UEnhancedBrainwaveAnalyzer::ComputeBasicStats(const TArray<double>& Data, double& OutMin, double& OutMax, double& OutMean, double& OutStd)
{
    if (Data.Num() == 0)
    {
        OutMin = OutMax = OutMean = OutStd = 0.0;
        return;
    }
    OutMin = Data[0];
    OutMax = Data[0];
    double Sum = 0.0;
    for (double V : Data)
    {
        OutMin = FMath::Min(OutMin, V);
        OutMax = FMath::Max(OutMax, V);
        Sum += V;
    }
    OutMean = Sum / static_cast<double>(Data.Num());
    double VarSum = 0.0;
    for (double V : Data)
    {
        const double D = V - OutMean;
        VarSum += D * D;
    }
    OutStd = (Data.Num() > 1) ? FMath::Sqrt(VarSum / static_cast<double>(Data.Num())) : 0.0;
}

FChakraSystemAnalysis UEnhancedBrainwaveAnalyzer::AnalyzeChakraSystem(const TArray<double>& OptionalFrequencies)
{
    FChakraSystemAnalysis Out;

    TArray<double> Energies;
    for (int32 i = 0; i < ChakraOrder.Num(); ++i)
    {
        const FName Key = ChakraOrder[i];
        const FChakraData* Chakra = Chakras.Find(Key);
        if (!Chakra) continue;
        const double Freq = (OptionalFrequencies.IsValidIndex(i)) ? OptionalFrequencies[i] : Chakra->Frequency;

        FChakraAnalysis CA;
        CA.Chakra = *Chakra;
        CA.Frequency = Freq;
        CA.Quantum = CalculateQuantumCoherence(Freq);
        CA.DNA = CalculateDNAResonance(Freq);
        CA.Brainwave = CalculateWavelengthMetrics(Freq);
        CA.EnergyLevel = CA.Quantum.EnergyJoules;
        CA.ActivationScore = CA.Quantum.CoherenceFactor * CA.DNA.ResonanceStrength;

        Out.IndividualChakras.Add(Key, CA);
        Out.SystemMetrics.TotalEnergy += CA.EnergyLevel;
        Out.SystemMetrics.CoherenceSum += CA.Quantum.CoherenceFactor;
        Out.SystemMetrics.EnergyDistribution.Add(Key.ToString(), CA.EnergyLevel);
        Energies.Add(CA.EnergyLevel);
    }

    double EMin, EMax, EMean, EStd;
    ComputeBasicStats(Energies, EMin, EMax, EMean, EStd);
    Out.SystemMetrics.BalanceScore = (EMean > 0.0) ? (1.0 - (EStd / EMean)) : 0.0;

    double BestEnergy = -1.0;
    for (const auto& Pair : Out.SystemMetrics.EnergyDistribution)
    {
        if (Pair.Value > BestEnergy)
        {
            BestEnergy = Pair.Value;
            Out.SystemMetrics.DominantChakra = Pair.Key;
        }
    }

    Out.Recommendations = GenerateRecommendations(Out.IndividualChakras);
    return Out;
}

void UEnhancedBrainwaveAnalyzer::GenerateFrequencyRange(double MinFreq, double MaxFreq, int32 NumFrequencies, TArray<double>& OutFrequencies) const
{
    const int32 ClampedNum = FMath::Min(NumFrequencies, MaxFrequencies);
    const int32 NumLog = FMath::Max(0, static_cast<int32>(ClampedNum * 0.7));
    const int32 NumLin = ClampedNum - NumLog;

    OutFrequencies.Reset(ClampedNum);
    OutFrequencies.Reserve(ClampedNum);

    const double LogMin = FMath::LogX(10.0, FMath::Max(1e-12, MinFreq));
    const double LogMax = FMath::LogX(10.0, FMath::Max(MinFreq + 1e-12, MaxFreq));

    for (int32 i = 0; i < NumLog; ++i)
    {
        const double T = (NumLog > 1) ? static_cast<double>(i) / static_cast<double>(NumLog - 1) : 0.0;
        const double LogVal = FMath::Lerp(LogMin, LogMax, T);
        OutFrequencies.Add(FMath::Pow(10.0, LogVal));
    }

    for (int32 i = 0; i < NumLin; ++i)
    {
        const double T = (NumLin > 1) ? static_cast<double>(i) / static_cast<double>(NumLin - 1) : 0.0;
        OutFrequencies.Add(FMath::Lerp(MinFreq, MaxFreq, T));
    }

    OutFrequencies.Sort();

    TArray<double> Unique; Unique.Reserve(OutFrequencies.Num());
    double* Prev = nullptr;
    for (double V : OutFrequencies)
    {
        if (!Prev || !FMath::IsNearlyEqual(*Prev, V))
        {
            Unique.Add(V);
            Prev = &Unique.Last();
        }
    }
    if (Unique.Num() > ClampedNum)
    {
        Unique.SetNum(ClampedNum);
    }
    OutFrequencies = MoveTemp(Unique);
}

FComprehensiveAnalysis UEnhancedBrainwaveAnalyzer::GenerateComprehensiveFrequencyAnalysis(double MinFreq, double MaxFreq, int32 NumFrequencies)
{
    FComprehensiveAnalysis Out;
    Out.MinFrequency = MinFreq;
    Out.MaxFrequency = MaxFreq;
    Out.NumFrequencies = NumFrequencies;

    TArray<double> Frequencies;
    GenerateFrequencyRange(MinFreq, MaxFreq, NumFrequencies, Frequencies);

    Out.AnalysisResults.Frequencies = Frequencies;
    Out.AnalysisResults.Wavelengths.Reserve(Frequencies.Num());
    Out.AnalysisResults.Metrics.Reserve(Frequencies.Num());
    Out.AnalysisResults.QuantumData.Reserve(Frequencies.Num());
    Out.AnalysisResults.DNAResonance.Reserve(Frequencies.Num());

    TMap<FString, int32> BandCounts;

    for (double Freq : Frequencies)
    {
        const double Wavelength = (Freq > 0.0) ? (SpeedOfLight / Freq) : 0.0;
        Out.AnalysisResults.Wavelengths.Add(Wavelength);

        const FWavelengthMetrics Metrics = CalculateWavelengthMetrics(Freq);
        Out.AnalysisResults.Metrics.Add(Metrics);
        Out.AnalysisResults.QuantumData.Add(Metrics.Quantum);
        Out.AnalysisResults.DNAResonance.Add(Metrics.DNA);

        const FString Band = Metrics.WavelengthClass;
        BandCounts.FindOrAdd(Band) += 1;
    }

    Out.SummaryStatistics.TotalAnalyzed = Frequencies.Num();
    ComputeBasicStats(Out.AnalysisResults.Frequencies, Out.SummaryStatistics.FreqMin, Out.SummaryStatistics.FreqMax, Out.SummaryStatistics.FreqMean, Out.SummaryStatistics.FreqStd);
    ComputeBasicStats(Out.AnalysisResults.Wavelengths, Out.SummaryStatistics.WaveMin, Out.SummaryStatistics.WaveMax, Out.SummaryStatistics.WaveMean, Out.SummaryStatistics.WaveStd);
    Out.SummaryStatistics.BandDistribution = BandCounts;

    for (const auto& Pair : BandCounts)
    {
        const double Pct = (Frequencies.Num() > 0) ? (static_cast<double>(Pair.Value) / static_cast<double>(Frequencies.Num())) * 100.0 : 0.0;
        Out.SummaryStatistics.BandPercentages.Add(Pair.Key, Pct);
    }

    return Out;
}

bool UEnhancedBrainwaveAnalyzer::ExportComprehensiveData(const FComprehensiveAnalysis& ComprehensiveResults, const FChakraSystemAnalysis& ChakraResults, const FString& Filename) const
{
    TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();

    Root->SetStringField(TEXT("timestamp"), FDateTime::Now().ToIso8601());

    TSharedRef<FJsonObject> Meta = MakeShared<FJsonObject>();
    Meta->SetStringField(TEXT("analyzer_version"), TEXT("2.0"));
    Meta->SetNumberField(TEXT("precision_decimal_places"), 15);
    Meta->SetNumberField(TEXT("max_frequencies"), MaxFrequencies);
    Root->SetObjectField(TEXT("metadata"), Meta);

    TSharedRef<FJsonObject> Params = MakeShared<FJsonObject>();
    Params->SetNumberField(TEXT("min_frequency"), ComprehensiveResults.MinFrequency);
    Params->SetNumberField(TEXT("max_frequency"), ComprehensiveResults.MaxFrequency);
    Params->SetNumberField(TEXT("num_frequencies"), ComprehensiveResults.NumFrequencies);

    TSharedRef<FJsonObject> Summary = MakeShared<FJsonObject>();
    Summary->SetNumberField(TEXT("total_analyzed"), ComprehensiveResults.SummaryStatistics.TotalAnalyzed);
    Summary->SetNumberField(TEXT("frequency_min"), ComprehensiveResults.SummaryStatistics.FreqMin);
    Summary->SetNumberField(TEXT("frequency_max"), ComprehensiveResults.SummaryStatistics.FreqMax);
    Summary->SetNumberField(TEXT("frequency_mean"), ComprehensiveResults.SummaryStatistics.FreqMean);
    Summary->SetNumberField(TEXT("frequency_std"), ComprehensiveResults.SummaryStatistics.FreqStd);
    Summary->SetNumberField(TEXT("wavelength_min"), ComprehensiveResults.SummaryStatistics.WaveMin);
    Summary->SetNumberField(TEXT("wavelength_max"), ComprehensiveResults.SummaryStatistics.WaveMax);
    Summary->SetNumberField(TEXT("wavelength_mean"), ComprehensiveResults.SummaryStatistics.WaveMean);
    Summary->SetNumberField(TEXT("wavelength_std"), ComprehensiveResults.SummaryStatistics.WaveStd);

    TSharedRef<FJsonObject> BandDist = MakeShared<FJsonObject>();
    for (const auto& Pair : ComprehensiveResults.SummaryStatistics.BandDistribution)
    {
        BandDist->SetNumberField(Pair.Key, Pair.Value);
    }
    Summary->SetObjectField(TEXT("band_distribution"), BandDist);

    TSharedRef<FJsonObject> BandPct = MakeShared<FJsonObject>();
    for (const auto& Pair : ComprehensiveResults.SummaryStatistics.BandPercentages)
    {
        BandPct->SetNumberField(Pair.Key, Pair.Value);
    }
    Summary->SetObjectField(TEXT("band_percentages"), BandPct);

    TSharedRef<FJsonObject> FreqAnalysis = MakeShared<FJsonObject>();
    TArray<TSharedPtr<FJsonValue>> FreqArray;
    TArray<TSharedPtr<FJsonValue>> WaveArray;
    for (int32 i = 0; i < ComprehensiveResults.AnalysisResults.Frequencies.Num(); ++i)
    {
        FreqArray.Add(MakeShared<FJsonValueNumber>(ComprehensiveResults.AnalysisResults.Frequencies[i]));
        WaveArray.Add(MakeShared<FJsonValueNumber>(ComprehensiveResults.AnalysisResults.Wavelengths[i]));
    }
    FreqAnalysis->SetArrayField(TEXT("frequencies"), FreqArray);
    FreqAnalysis->SetArrayField(TEXT("wavelengths"), WaveArray);
    FreqAnalysis->SetObjectField(TEXT("summary"), Summary);
    FreqAnalysis->SetObjectField(TEXT("parameters"), Params);
    Root->SetObjectField(TEXT("frequency_analysis"), FreqAnalysis);

    TSharedRef<FJsonObject> ChakraRoot = MakeShared<FJsonObject>();
    TSharedRef<FJsonObject> Individual = MakeShared<FJsonObject>();
    for (const auto& Pair : ChakraResults.IndividualChakras)
    {
        const FName Name = Pair.Key;
        const FChakraAnalysis& A = Pair.Value;
        TSharedRef<FJsonObject> C = MakeShared<FJsonObject>();

        TSharedRef<FJsonObject> CD = MakeShared<FJsonObject>();
        CD->SetStringField(TEXT("name"), A.Chakra.Name);
        CD->SetNumberField(TEXT("frequency"), A.Chakra.Frequency);
        CD->SetStringField(TEXT("color"), A.Chakra.ColorHex);
        CD->SetStringField(TEXT("element"), A.Chakra.Element);
        CD->SetStringField(TEXT("location"), A.Chakra.Location);
        TArray<TSharedPtr<FJsonValue>> Props;
        for (const FString& P : A.Chakra.Properties) Props.Add(MakeShared<FJsonValueString>(P));
        CD->SetArrayField(TEXT("properties"), Props);
        C->SetObjectField(TEXT("chakra_data"), CD);

        C->SetNumberField(TEXT("frequency"), A.Frequency);
        C->SetNumberField(TEXT("energy_level"), A.EnergyLevel);
        C->SetNumberField(TEXT("activation_score"), A.ActivationScore);
        Individual->SetObjectField(Name.ToString(), C);
    }
    ChakraRoot->SetObjectField(TEXT("individual_chakras"), Individual);

    TSharedRef<FJsonObject> System = MakeShared<FJsonObject>();
    System->SetNumberField(TEXT("total_energy"), ChakraResults.SystemMetrics.TotalEnergy);
    System->SetNumberField(TEXT("coherence_sum"), ChakraResults.SystemMetrics.CoherenceSum);
    System->SetNumberField(TEXT("balance_score"), ChakraResults.SystemMetrics.BalanceScore);
    System->SetStringField(TEXT("dominant_chakra"), ChakraResults.SystemMetrics.DominantChakra);
    TSharedRef<FJsonObject> Dist = MakeShared<FJsonObject>();
    for (const auto& Pair : ChakraResults.SystemMetrics.EnergyDistribution)
    {
        Dist->SetNumberField(Pair.Key, Pair.Value);
    }
    System->SetObjectField(TEXT("energy_distribution"), Dist);
    ChakraRoot->SetObjectField(TEXT("system_metrics"), System);

    TArray<TSharedPtr<FJsonValue>> Recs;
    for (const FString& R : ChakraResults.Recommendations) Recs.Add(MakeShared<FJsonValueString>(R));
    ChakraRoot->SetArrayField(TEXT("recommendations"), Recs);

    Root->SetObjectField(TEXT("chakra_analysis"), ChakraRoot);

    FString OutStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutStr);
    const bool bOk = FJsonSerializer::Serialize(Root, Writer);
    if (!bOk) return false;

    const FString AbsPath = FPaths::IsRelative(Filename) ? FPaths::ConvertRelativePathToFull(Filename) : Filename;
    return FFileHelper::SaveStringToFile(OutStr, *AbsPath);
}

FChakraAnalysis UEnhancedBrainwaveAnalyzer::EnhancedChakraAnalysis(FName ChakraName)
{
    FChakraAnalysis Out;
    const FChakraData* Data = Chakras.Find(ChakraName);
    if (!Data)
    {
        return Out;
    }

    const double BaseFreq = Data->Frequency;
    TArray<double> Freqs; Freqs.Reserve(10);
    for (int32 i = 0; i < 10; ++i)
    {
        const double F = BaseFreq * (0.9 + 0.02 * static_cast<double>(i));
        Freqs.Add(F);
    }

    int32 BestIdx = 0;
    double BestScore = -1.0;
    struct FTempRes { double Frequency; FQuantumMetrics Q; FDNAResonance D; FWavelengthMetrics M; };
    TArray<FTempRes> Results; Results.Reserve(Freqs.Num());

    for (int32 i = 0; i < Freqs.Num(); ++i)
    {
        const double F = Freqs[i];
        FTempRes R;
        R.Frequency = F;
        R.M = CalculateWavelengthMetrics(F);
        R.Q = R.M.Quantum;
        R.D = R.M.DNA;
        Results.Add(R);

        const double Score = R.Q.CoherenceFactor * R.D.ResonanceStrength;
        if (Score > BestScore)
        {
            BestScore = Score;
            BestIdx = i;
        }
    }

    const FTempRes& Opt = Results[BestIdx];
    Out.Chakra = *Data;
    Out.Frequency = Opt.Frequency;
    Out.Quantum = Opt.Q;
    Out.DNA = Opt.D;
    Out.Brainwave = Opt.M;
    Out.EnergyLevel = Out.Quantum.EnergyJoules;
    Out.ActivationScore = BestScore;
    return Out;
}
