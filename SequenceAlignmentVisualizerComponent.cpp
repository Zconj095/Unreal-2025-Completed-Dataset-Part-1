#include "SequenceAlignmentVisualizerComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Algo/Reverse.h"

namespace
{
struct FSequenceAlignment
{
    int32 MatchScore;
    int32 GapPenalty;

    FSequenceAlignment(int32 InMatchScore, int32 InGapPenalty)
        : MatchScore(InMatchScore), GapPenalty(InGapPenalty)
    {
    }

    TArray<TArray<int32>> AlignSequences(const FString& SeqA, const FString& SeqB) const
    {
        const int32 Rows = SeqA.Len() + 1;
        const int32 Cols = SeqB.Len() + 1;
        TArray<TArray<int32>> Matrix;
        Matrix.SetNum(Rows);

        for (int32 Row = 0; Row < Rows; ++Row)
        {
            Matrix[Row].Init(0, Cols);
        }

        for (int32 Row = 1; Row < Rows; ++Row)
        {
            Matrix[Row][0] = Matrix[Row - 1][0] - GapPenalty;
        }

        for (int32 Col = 1; Col < Cols; ++Col)
        {
            Matrix[0][Col] = Matrix[0][Col - 1] - GapPenalty;
        }

        for (int32 Row = 1; Row < Rows; ++Row)
        {
            for (int32 Col = 1; Col < Cols; ++Col)
            {
                const int32 MatchBonus = (SeqA[Row - 1] == SeqB[Col - 1]) ? MatchScore : 0;
                const int32 DiagonalScore = Matrix[Row - 1][Col - 1] + MatchBonus;
                const int32 UpScore = Matrix[Row - 1][Col] - GapPenalty;
                const int32 LeftScore = Matrix[Row][Col - 1] - GapPenalty;
                Matrix[Row][Col] = FMath::Max3(DiagonalScore, UpScore, LeftScore);
            }
        }

        return Matrix;
    }

    TPair<FString, FString> Traceback(const FString& SeqA, const FString& SeqB, const TArray<TArray<int32>>& Matrix) const
    {
        int32 Row = SeqA.Len();
        int32 Col = SeqB.Len();
        TArray<TCHAR> AlignedA;
        TArray<TCHAR> AlignedB;

        while (Row > 0 || Col > 0)
        {
            const int32 CurrentScore = Matrix[Row][Col];

            if (Row > 0 && Col > 0)
            {
                const int32 MatchBonus = (SeqA[Row - 1] == SeqB[Col - 1]) ? MatchScore : 0;
                if (CurrentScore == Matrix[Row - 1][Col - 1] + MatchBonus)
                {
                    AlignedA.Add(SeqA[Row - 1]);
                    AlignedB.Add(SeqB[Col - 1]);
                    --Row;
                    --Col;
                    continue;
                }
            }

            if (Row > 0 && CurrentScore == Matrix[Row - 1][Col] - GapPenalty)
            {
                AlignedA.Add(SeqA[Row - 1]);
                AlignedB.Add(TEXT('-'));
                --Row;
                continue;
            }

            if (Col > 0 && CurrentScore == Matrix[Row][Col - 1] - GapPenalty)
            {
                AlignedA.Add(TEXT('-'));
                AlignedB.Add(SeqB[Col - 1]);
                --Col;
                continue;
            }

            if (Row > 0 && Col > 0)
            {
                AlignedA.Add(SeqA[Row - 1]);
                AlignedB.Add(SeqB[Col - 1]);
                --Row;
                --Col;
            }
            else if (Row > 0)
            {
                AlignedA.Add(SeqA[Row - 1]);
                AlignedB.Add(TEXT('-'));
                --Row;
            }
            else if (Col > 0)
            {
                AlignedA.Add(TEXT('-'));
                AlignedB.Add(SeqB[Col - 1]);
                --Col;
            }
        }

        Algo::Reverse(AlignedA);
        Algo::Reverse(AlignedB);

        FString ResultA;
        FString ResultB;
        ResultA.Reserve(AlignedA.Num());
        ResultB.Reserve(AlignedB.Num());

        for (TCHAR Character : AlignedA)
        {
            ResultA.AppendChar(Character);
        }

        for (TCHAR Character : AlignedB)
        {
            ResultB.AppendChar(Character);
        }

        return {ResultA, ResultB};
    }
};
}

USequenceAlignmentVisualizerComponent::USequenceAlignmentVisualizerComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USequenceAlignmentVisualizerComponent::BeginPlay()
{
    Super::BeginPlay();
    VisualizeAlignment();
}

void USequenceAlignmentVisualizerComponent::VisualizeAlignment() const
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    FSequenceAlignment Aligner(MatchScore, GapPenalty);
    const TArray<TArray<int32>> ScoreMatrix = Aligner.AlignSequences(SequenceA, SequenceB);
    const TPair<FString, FString> AlignmentPair = Aligner.Traceback(SequenceA, SequenceB, ScoreMatrix);
    const int32 Length = AlignmentPair.Key.Len();

    if (Length == 0)
    {
        return;
    }

    const FVector BaseLocation = GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;

    for (int32 Index = 0; Index < Length; ++Index)
    {
        const bool bIsMatch = AlignmentPair.Key[Index] == AlignmentPair.Value[Index] && AlignmentPair.Key[Index] != TEXT('-');
        const TSubclassOf<AActor> ActorClass = bIsMatch ? MatchActor : GapActor;

        if (!ActorClass)
        {
            continue;
        }

        const FVector SpawnLocation = BaseLocation + FVector(HorizontalSpacing * Index, 0.0f, 0.0f);
        World->SpawnActor<AActor>(ActorClass, SpawnLocation, FRotator::ZeroRotator);
    }
}
