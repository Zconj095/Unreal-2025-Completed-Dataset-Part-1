#include "MatrixKnowledgeUnits.h"
#include "Engine/World.h"

#include "Misc/Guid.h"

AMatrixKnowledgeUnits::AMatrixKnowledgeUnits()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMatrixKnowledgeUnits::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Knowledge Units System Initialized."));
}

void AMatrixKnowledgeUnits::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    AddUnitTimer += DeltaSeconds;
    ProcessUnitsTimer += DeltaSeconds;
    RetrieveUnitsTimer += DeltaSeconds;

    if (AddUnitTimer >= AddUnitInterval)
    {
        const float TimeSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
        AddKnowledgeUnit(FString::Printf(TEXT("Generated data at %.2f"), TimeSeconds));
        AddUnitTimer = 0.f;
    }

    if (ProcessUnitsTimer >= ProcessUnitsInterval)
    {
        ProcessKnowledgeUnits();
        ProcessUnitsTimer = 0.f;
    }

    if (RetrieveUnitsTimer >= RetrieveUnitsInterval)
    {
        RetrieveKnowledgeUnits();
        RetrieveUnitsTimer = 0.f;
    }
}

void AMatrixKnowledgeUnits::AddKnowledgeUnit(const FString& Data)
{
    FKnowledgeUnit Unit(Data);
    UE_LOG(LogTemp, Log, TEXT("Knowledge Unit Added - ID: %s, Data: %s"), *Unit.UnitID, *Data);
    KnowledgeUnits.Add(MoveTemp(Unit));
}

void AMatrixKnowledgeUnits::ProcessKnowledgeUnits()
{
    UE_LOG(LogTemp, Log, TEXT("Processing knowledge units into energy..."));

    for (FKnowledgeUnit& Unit : KnowledgeUnits)
    {
        if (!Unit.bIsProcessed)
        {
            const float UnitEnergy = CalculateUnitEnergy(Unit.Data);
            TotalEnergy += UnitEnergy;
            Unit.MarkProcessed();
            UE_LOG(LogTemp, Log, TEXT("Unit '%s' converted to %f energy units."), *Unit.UnitID, UnitEnergy);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Total Energy: %f units."), TotalEnergy);
}

float AMatrixKnowledgeUnits::CalculateUnitEnergy(const FString& Data) const
{
    TArray<FString> Words;
    const FString Trimmed = Data; // FString::TrimStartAndEnd returns a TCHAR*, so handle simply
    Trimmed.ParseIntoArray(Words, TEXT(" "), true);
    const int32 WordCount = Words.Num();

    float Energy = PI * 22.831f * FMath::Pow(2.f, static_cast<float>(WordCount));
    Energy /= 42.185f * FMath::Sin(FMath::DegreesToRadians(32.81f));
    Energy *= 0.6681f;    // 66% split factor
    Energy *= 0.971346f;  // 2.8654% flux capacitance adjustment
    return Energy;
}

void AMatrixKnowledgeUnits::RetrieveKnowledgeUnits() const
{
    UE_LOG(LogTemp, Log, TEXT("Retrieving all knowledge units..."));
    for (const FKnowledgeUnit& Unit : KnowledgeUnits)
    {
        UE_LOG(LogTemp, Log, TEXT("Unit - ID: %s, Data: %s, Processed: %s"), *Unit.UnitID, *Unit.Data, Unit.bIsProcessed ? TEXT("true") : TEXT("false"));
    }
}

