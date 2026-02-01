#include "ElementFieldArray.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

AElementFieldArray::AElementFieldArray()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AElementFieldArray::BeginPlay()
{
    Super::BeginPlay();

    if (bAutoInitializeOnBeginPlay)
    {
        InitializeField();
    }
}

void AElementFieldArray::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bAutoSimulate)
    {
        SimulateFieldEvolution(DeltaSeconds);
    }

    if (bAutoVisualize)
    {
        VisualizeField();
    }
}

void AElementFieldArray::InitializeField()
{
    if (SizeX <= 0 || SizeY <= 0)
    {
        FieldArray.Reset();
        return;
    }

    FieldArray.SetNum(GetElementCount());

    for (int32 I = 0; I < SizeX; ++I)
    {
        for (int32 J = 0; J < SizeY; ++J)
        {
            const int32 Index = GetIndex(I, J, SizeX);
            FQuantumElement& Elem = FieldArray[Index];

            Elem.Position = FVector((float)I, (float)J, 0.f);
            Elem.EnergyLevel = FMath::RandRange(0.f, 100.f);

            Elem.ProbabilityWaveFunction.Real = FMath::FRand();
            Elem.ProbabilityWaveFunction.Imag = FMath::FRand();

            Elem.HyperDimensionalCoordXYZ = FVector(FMath::FRand(), FMath::FRand(), FMath::FRand());
            Elem.HyperDimensionalCoordW = FMath::FRand();
        }
    }
}

void AElementFieldArray::SimulateFieldEvolution(float DeltaTime)
{
    if (FieldArray.Num() != GetElementCount())
    {
        return;
    }

    for (int32 I = 0; I < SizeX; ++I)
    {
        for (int32 J = 0; J < SizeY; ++J)
        {
            const int32 Index = GetIndex(I, J, SizeX);
            FQuantumElement& Elem = FieldArray[Index];

            FComplexSimple NewWave;
            NewWave.Real = FMath::FRand();
            NewWave.Imag = FMath::FRand();
            Elem.TransitionState(NewWave, DeltaTime);
        }
    }
}

float AElementFieldArray::CalculateTotalFieldEnergy() const
{
    if (FieldArray.Num() != SizeX * SizeY)
    {
        return 0.f;
    }

    float TotalEnergy = 0.f;
    for (int32 I = 0; I < SizeX; ++I)
    {
        for (int32 J = 0; J < SizeY; ++J)
        {
            const int32 Index = GetIndex(I, J, SizeX);
            TotalEnergy += FieldArray[Index].EnergyLevel;
        }
    }
    return TotalEnergy;
}

void AElementFieldArray::VisualizeField()
{
    if (!GetWorld() || FieldArray.Num() != GetElementCount())
    {
        return;
    }

    for (int32 I = 0; I < SizeX; ++I)
    {
        for (int32 J = 0; J < SizeY; ++J)
        {
            const int32 Index = GetIndex(I, J, SizeX);
            const FQuantumElement& Elem = FieldArray[Index];

            const float T = FMath::Clamp(Elem.EnergyLevel / 100.f, 0.f, 1.f);
            const FLinearColor Linear = FLinearColor::LerpUsingHSV(FLinearColor::Blue, FLinearColor::Red, T);
            const FColor DebugColor = Linear.ToFColor(true);

            const FVector Start = Elem.Position;
            const FVector End = Start + FVector::UpVector * 10.f;
            DrawDebugLine(GetWorld(), Start, End, DebugColor, false, 0.f, 0, 1.5f);
        }
    }
}

