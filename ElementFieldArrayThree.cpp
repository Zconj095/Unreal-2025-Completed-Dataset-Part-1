#include "ElementFieldArrayThree.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

namespace
{
    static int32 ElementTypeCount()
    {
        return 6; // Fire, Water, Earth, Air, Lightning, Ice
    }
}

AElementFieldArrayThree::AElementFieldArrayThree()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AElementFieldArrayThree::BeginPlay()
{
    Super::BeginPlay();

    if (bAutoInitializeOnBeginPlay)
    {
        InitializeField();
        if (bAutoBuildNetwork)
        {
            BuildPossibilityNetwork();
        }
    }
}

void AElementFieldArrayThree::Tick(float DeltaSeconds)
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

void AElementFieldArrayThree::InitializeField()
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
            FQuantumElementThree& Elem = FieldArray[Index];

            Elem.Position = FVector((float)I, (float)J, 0.f);
            Elem.EnergyLevel = FMath::RandRange(0.f, 100.f);

            Elem.ProbabilityWaveFunction.Real = FMath::FRand();
            Elem.ProbabilityWaveFunction.Imag = FMath::FRand();

            Elem.HyperDimensionalCoordXYZ = FVector(FMath::FRand(), FMath::FRand(), FMath::FRand());
            Elem.HyperDimensionalCoordW = FMath::FRand();

            const int32 RandIndex = FMath::RandRange(0, ElementTypeCount() - 1);
            Elem.ElementalAttribute = static_cast<EElementalTypeTwo>(RandIndex);
            Elem.ElementalIntensity = FMath::FRandRange(0.1f, 1.f);

            Elem.ClearConnections();
        }
    }
}

void AElementFieldArrayThree::BuildPossibilityNetwork()
{
    if (FieldArray.Num() != GetElementCount())
    {
        return;
    }

    // Clear existing
    for (FQuantumElementThree& Elem : FieldArray)
    {
        Elem.ClearConnections();
    }

    for (int32 I = 0; I < SizeX; ++I)
    {
        for (int32 J = 0; J < SizeY; ++J)
        {
            const int32 CurrIdx = GetIndex(I, J, SizeX);
            if (I > 0) AddConnectionBetweenElements(CurrIdx, GetIndex(I - 1, J, SizeX));
            if (I < SizeX - 1) AddConnectionBetweenElements(CurrIdx, GetIndex(I + 1, J, SizeX));
            if (J > 0) AddConnectionBetweenElements(CurrIdx, GetIndex(I, J - 1, SizeX));
            if (J < SizeY - 1) AddConnectionBetweenElements(CurrIdx, GetIndex(I, J + 1, SizeX));
        }
    }
}

void AElementFieldArrayThree::AddConnectionBetweenElements(int32 AIdx, int32 BIdx)
{
    if (!FieldArray.IsValidIndex(AIdx) || !FieldArray.IsValidIndex(BIdx))
    {
        return;
    }
    const float Probability = FMath::FRand();
    FieldArray[AIdx].AddConnection(BIdx, Probability);
    FieldArray[BIdx].AddConnection(AIdx, Probability);
}

void AElementFieldArrayThree::SimulateFieldEvolution(float DeltaTime)
{
    if (FieldArray.Num() != GetElementCount())
    {
        return;
    }

    // Mirror Unity: for each connection, if Random < probability then transition toward that target's state
    for (int32 Index = 0; Index < FieldArray.Num(); ++Index)
    {
        FieldArray[Index].TransitionBasedOnNetwork(DeltaTime, FieldArray);
    }
}

void AElementFieldArrayThree::VisualizeField()
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
            const FQuantumElementThree& Elem = FieldArray[Index];

            const FColor DotColor = ElementalTypeToColor(Elem.ElementalAttribute);
            const FVector Start = Elem.Position;
            const FVector End = Start + FVector::UpVector * 10.f;
            DrawDebugLine(GetWorld(), Start, End, DotColor, false, 0.f, 0, 1.5f);

            for (const FElementConnection& C : Elem.PossibleConnections)
            {
                if (!FieldArray.IsValidIndex(C.TargetIndex)) continue;
                const FVector TargetPos = FieldArray[C.TargetIndex].Position;
                DrawDebugLine(GetWorld(), Elem.Position, TargetPos, FColor::Yellow, false, 0.f, 0, 0.5f);
            }
        }
    }
}

FColor AElementFieldArrayThree::ElementalTypeToColor(EElementalTypeTwo Type)
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
