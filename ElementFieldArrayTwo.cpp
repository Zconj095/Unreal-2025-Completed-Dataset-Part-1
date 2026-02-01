#include "ElementFieldArrayTwo.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

namespace
{
    static int32 ElementTypeCount()
    {
        // Keep in sync with EElementalTypeTwo entries
        return 6; // Fire, Water, Earth, Air, Lightning, Ice
    }
}

AElementFieldArrayTwo::AElementFieldArrayTwo()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AElementFieldArrayTwo::BeginPlay()
{
    Super::BeginPlay();

    if (bAutoInitializeOnBeginPlay)
    {
        InitializeField();
    }
}

void AElementFieldArrayTwo::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (bAutoSimulate)
    {
        SimulateFieldEvolution(DeltaSeconds);
        SimulateElementalInteractions();
    }

    if (bAutoVisualize)
    {
        VisualizeField();
    }
}

void AElementFieldArrayTwo::InitializeField()
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

            FQuantumElementTwo& Elem = FieldArray[Index];
            Elem.Position = FVector((float)I, (float)J, 0.f);
            Elem.Energy = FMath::RandRange(0.f, 100.f);

            Elem.WaveFunction.Real = FMath::FRand();
            Elem.WaveFunction.Imag = FMath::FRand();

            Elem.HyperCoordXYZ = FVector(FMath::FRand(), FMath::FRand(), FMath::FRand());
            Elem.HyperCoordW = FMath::FRand();

            const int32 RandIndex = FMath::RandRange(0, ElementTypeCount() - 1);
            Elem.ElementalAttribute = static_cast<EElementalTypeTwo>(RandIndex);
            Elem.ElementalIntensity = FMath::FRandRange(0.1f, 1.f);
        }
    }
}

void AElementFieldArrayTwo::SimulateFieldEvolution(float DeltaTime)
{
    if (FieldArray.Num() != GetElementCount())
    {
        // Not initialized
        return;
    }

    for (int32 I = 0; I < SizeX; ++I)
    {
        for (int32 J = 0; J < SizeY; ++J)
        {
            const int32 Index = GetIndex(I, J, SizeX);
            FQuantumElementTwo& Elem = FieldArray[Index];

            FComplexSimple NewWave;
            NewWave.Real = FMath::FRand();
            NewWave.Imag = FMath::FRand();
            Elem.TransitionState(NewWave, DeltaTime);
        }
    }
}

void AElementFieldArrayTwo::SimulateElementalInteractions()
{
    if (FieldArray.Num() != GetElementCount())
    {
        // Not initialized
        return;
    }

    for (int32 I = 0; I < SizeX - 1; ++I)
    {
        for (int32 J = 0; J < SizeY - 1; ++J)
        {
            const int32 CurrIdx = GetIndex(I, J, SizeX);
            const int32 RightIdx = GetIndex(I + 1, J, SizeX);
            const int32 DownIdx = GetIndex(I, J + 1, SizeX);

            FQuantumElementTwo& Current = FieldArray[CurrIdx];
            FQuantumElementTwo& Right = FieldArray[RightIdx];
            FQuantumElementTwo& Down = FieldArray[DownIdx];

            Current.InteractWith(Right);
            Current.InteractWith(Down);
        }
    }
}

void AElementFieldArrayTwo::VisualizeField()
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
            const FQuantumElementTwo& Elem = FieldArray[Index];
            const FColor Color = ElementalTypeToColor(Elem.ElementalAttribute);
            const FVector Start = Elem.Position;
            const FVector End = Start + FVector::UpVector * 10.f; // small vertical line
            DrawDebugLine(GetWorld(), Start, End, Color, false, 0.f, 0, 1.5f);
        }
    }
}

FColor AElementFieldArrayTwo::ElementalTypeToColor(EElementalTypeTwo Type)
{
    switch (Type)
    {
    case EElementalTypeTwo::Fire:      return FColor::Red;
    case EElementalTypeTwo::Water:     return FColor::Blue;
    case EElementalTypeTwo::Earth:     return FColor::Green;
    case EElementalTypeTwo::Air:       return FColor::White;
    case EElementalTypeTwo::Lightning: return FColor::Yellow;
    case EElementalTypeTwo::Ice:       return FColor::Cyan;
    default:                           return FColor::Silver;
    }
}

