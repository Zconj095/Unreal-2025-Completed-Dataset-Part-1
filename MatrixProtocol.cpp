#include "MatrixProtocol.h"

AMatrixProtocol::AMatrixProtocol()
{
    PrimaryActorTick.bCanEverTick = true;
}

// Static protocol values for digits '0'..'9'
const int64 AMatrixProtocol::ProtocolFormula[10] = {
    228351LL,          // '0'
    35821LL,           // '1'
    9998721LL,         // '2'
    845632LL,          // '3'
    212164521LL,       // '4'
    8691LL,            // '5'
    425LL,             // '6'
    8521LL,            // '7'
    8956723561LL,      // '8'
    1010534765921LL    // '9'
};

void AMatrixProtocol::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Protocol Initialized."));
}

void AMatrixProtocol::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Increment timers
    ProcessPathTimer += DeltaSeconds;
    HandleUnknownDataTimer += DeltaSeconds;

    // Automate processing predefined paths
    if (ProcessPathTimer >= ProcessPathInterval)
    {
        HandleUnknownData(TEXT("08478510101820"));
        ProcessPathTimer = 0.f;
    }

    // Automate handling unknown data
    if (HandleUnknownDataTimer >= HandleUnknownDataInterval)
    {
        HandleUnknownData(TEXT("238947128471"));
        HandleUnknownDataTimer = 0.f;
    }
}

int64 AMatrixProtocol::ProcessPath(const FString& Path)
{
    FString Trimmed = Path;
    Trimmed.TrimStartAndEndInline();
    if (Trimmed.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid path provided."));
        return 0;
    }

    int64 Result = 0;
    for (TCHAR Ch : Trimmed)
    {
        if (FChar::IsDigit(Ch))
        {
            const int32 Index = static_cast<int32>(Ch - TEXT('0'));
            if (Index >= 0 && Index <= 9)
            {
                Result += ProtocolFormula[Index];
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid character '%c' in path. Ignored in calculation."), Ch);
        }
    }

    UE_LOG(LogTemp, Log, TEXT("Processed Path: %s, Result: %lld"), *Trimmed, Result);
    return Result;
}

double AMatrixProtocol::GenerateFormulaicResponse(int64 ComputedResult) const
{
    const double CriticalMalfunctionStandard = 22.7 * PI; // 22.7 * Pi
    const double Response = (static_cast<double>(ComputedResult) * 62889317241.0 / 321.0) / CriticalMalfunctionStandard;

    UE_LOG(LogTemp, Log, TEXT("Formulaic Response Generated: %f"), Response);
    return Response;
}

void AMatrixProtocol::HandleUnknownData(const FString& UnknownData)
{
    UE_LOG(LogTemp, Log, TEXT("Handling Unknown Data: %s"), *UnknownData);
    const int64 ComputedResult = ProcessPath(UnknownData);
    const double Response = GenerateFormulaicResponse(ComputedResult);

    UE_LOG(LogTemp, Log, TEXT("Unknown Data Processed - Final Response: %f"), Response);
}

