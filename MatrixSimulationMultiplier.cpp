#include "MatrixSimulationMultiplier.h"

AMatrixSimulationMultiplier::AMatrixSimulationMultiplier()
{
    PrimaryActorTick.bCanEverTick = true;

    // Default frequencies
    Frequencies = { 50.123, 76.543, 89.876, 101.234 };
}

void AMatrixSimulationMultiplier::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Simulation Multiplier Initialized."));
    SimulateFrequencies(); // Initial simulation on start
}

void AMatrixSimulationMultiplier::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Automated simulation at intervals
    Timer += DeltaSeconds;
    if (Timer >= SimulationInterval)
    {
        UE_LOG(LogTemp, Log, TEXT("Automated Simulation Triggered at Interval: %.2fs"), SimulationInterval);

        // Dynamically update numeric value and frequencies
        UpdateNumericValue();
        UpdateFrequencies();

        // Perform the simulation with updated values
        SimulateFrequencies();
        Timer = 0.f; // Reset timer
    }
}

double AMatrixSimulationMultiplier::CalculateMultiplier(double Frequency, int32 InNumericValue) const
{
    const double Step1 = Frequency + static_cast<double>(InNumericValue);
    const double Step2 = Step1 * 0.66781;
    const double Step3 = Step2 / 72.8391;
    const double Step4 = FMath::Pow(static_cast<float>(Step3), 2.0f); // Square
    const double Step5 = FMath::Pow(static_cast<float>(Step4), 3.0f); // Cube of the square
    const double Step6 = static_cast<double>(FMath::RoundHalfFromZero(static_cast<float>(Step5 * 10.0))) / 10.0; // Round to 10th
    const double Step7 = (Step6 * 100.0) - 1.0; // Decimal shift and subtract 1
    const double FinalResult = Step7 + 62.0; // Add 62 for final result

    // Debugging output for traceability
    UE_LOG(LogTemp, Log, TEXT("Multiplier Calculation for Frequency %f:"), Frequency);
    UE_LOG(LogTemp, Log, TEXT("Step 1 (Add): %f"), Step1);
    UE_LOG(LogTemp, Log, TEXT("Step 2 (Multiply by 0.66781): %f"), Step2);
    UE_LOG(LogTemp, Log, TEXT("Step 3 (Divide by 72.8391): %f"), Step3);
    UE_LOG(LogTemp, Log, TEXT("Step 4 (Square): %f"), Step4);
    UE_LOG(LogTemp, Log, TEXT("Step 5 (Cube): %f"), Step5);
    UE_LOG(LogTemp, Log, TEXT("Step 6 (Round): %f"), Step6);
    UE_LOG(LogTemp, Log, TEXT("Step 7 (Decimal Shift and Subtract 1): %f"), Step7);
    UE_LOG(LogTemp, Log, TEXT("Final Result (Add 62): %f"), FinalResult);

    return FinalResult;
}

void AMatrixSimulationMultiplier::SimulateFrequencies()
{
    UE_LOG(LogTemp, Log, TEXT("Starting Simulation for Multiple Frequencies..."));
    for (double Freq : Frequencies)
    {
        const double Result = CalculateMultiplier(Freq, NumericValue);
        UE_LOG(LogTemp, Log, TEXT("Frequency: %f, Result: %f"), Freq, Result);
    }
}

void AMatrixSimulationMultiplier::UpdateNumericValue()
{
    NumericValue = FMath::RandRange(1, 9); // Unity Random.Range(1,10)
    UE_LOG(LogTemp, Log, TEXT("Numeric Value Dynamically Updated: %d"), NumericValue);
}

void AMatrixSimulationMultiplier::UpdateFrequencies()
{
    Frequencies.Empty();
    Frequencies.Add(static_cast<double>(FMath::FRandRange(40.f, 120.f)));
    Frequencies.Add(static_cast<double>(FMath::FRandRange(40.f, 120.f)));
    Frequencies.Add(static_cast<double>(FMath::FRandRange(40.f, 120.f)));
    Frequencies.Add(static_cast<double>(FMath::FRandRange(40.f, 120.f)));

    UE_LOG(LogTemp, Log, TEXT("Frequencies Dynamically Updated:"));
    for (double Freq : Frequencies)
    {
        UE_LOG(LogTemp, Log, TEXT("Frequency: %f"), Freq);
    }
}
