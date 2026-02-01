// Converted from Unity MonoBehaviour SoulUnificationWithHebbian to Unreal ActorComponent.
#include "SoulUnificationComponent.h"
#include "Engine/World.h"

#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

USoulUnificationComponent::USoulUnificationComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USoulUnificationComponent::BeginPlay()
{
    Super::BeginPlay();
    InitializeHebbianWeights();
    UnifySouls();
}

void USoulUnificationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (bAutoVisualizeConnections)
    {
        DrawConnections();
    }
}

void USoulUnificationComponent::InitializeHebbianWeights()
{
    HebbianWeights.Empty();
    const int32 Count = Souls.Num();
    for (int32 I = 0; I < Count; ++I)
    {
        for (int32 J = I + 1; J < Count; ++J)
        {
            FIntPoint Key(I, J);
            HebbianWeights.Add(Key, FMath::FRandRange(0.1f, 0.5f));
        }
    }
}

void USoulUnificationComponent::UnifySouls()
{
    if (Souls.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("SoulUnificationComponent: No souls to merge."));
        return;
    }

    TArray<FSoulNode> WorkingSouls = Souls;
    TArray<float> AdjustedIntensities;
    AdjustedIntensities.SetNumZeroed(WorkingSouls.Num());

    for (int32 Index = 0; Index < WorkingSouls.Num(); ++Index)
    {
        float Intensity = WorkingSouls[Index].Intensity;
        for (const auto& Pair : HebbianWeights)
        {
            const FIntPoint Key = Pair.Key;
            if (Key.X == Index || Key.Y == Index)
            {
                Intensity *= Pair.Value;
            }
        }
        AdjustedIntensities[Index] = FMath::Clamp(Intensity, 0.0f, 1.0f);
    }

    FVector CombinedPosition = FVector::ZeroVector;
    FLinearColor BlendedColor = FLinearColor::Black;
    float TotalIntensity = 0.0f;

    for (int32 Index = 0; Index < WorkingSouls.Num(); ++Index)
    {
        const FSoulNode& Soul = WorkingSouls[Index];
        const float Intensity = AdjustedIntensities[Index];
        CombinedPosition += Soul.Position * Intensity;
        BlendedColor += Soul.SoulColor * Intensity;
        TotalIntensity += Intensity;
    }

    if (TotalIntensity > SMALL_NUMBER)
    {
        CombinedPosition /= TotalIntensity;
        BlendedColor /= WorkingSouls.Num();
    }
    else
    {
        CombinedPosition = FVector::ZeroVector;
        BlendedColor = FLinearColor::Black;
    }

    UnifiedSoul = FSoulNode();
    UnifiedSoul.Name = TEXT("Unified Soul");
    UnifiedSoul.Intensity = FMath::Clamp(TotalIntensity, 0.0f, 1.0f);
    UnifiedSoul.Position = CombinedPosition;
    UnifiedSoul.SoulColor = BlendedColor;

    UE_LOG(LogTemp, Log, TEXT("Unified Soul Created: %s"), *UnifiedSoul.Name);
}

void USoulUnificationComponent::HebbianLearning(int32 SoulIndexA, int32 SoulIndexB, float Delta)
{
    const int32 MinIndex = FMath::Min(SoulIndexA, SoulIndexB);
    const int32 MaxIndex = FMath::Max(SoulIndexA, SoulIndexB);
    if (MinIndex == MaxIndex || MinIndex < 0 || MaxIndex >= Souls.Num())
    {
        return;
    }

    FIntPoint Key(MinIndex, MaxIndex);
    if (HebbianWeights.Contains(Key))
    {
        float& Weight = HebbianWeights[Key];
        Weight = FMath::Clamp(Weight + Delta, 0.0f, 1.0f);
        UE_LOG(LogTemp, Log, TEXT("Updated Hebbian Weight (%d, %d): %.3f"), MinIndex, MaxIndex, Weight);
    }
}

float USoulUnificationComponent::GetConnectionWeight(int32 A, int32 B) const
{
    const int32 MinIndex = FMath::Min(A, B);
    const int32 MaxIndex = FMath::Max(A, B);
    const FIntPoint Key(MinIndex, MaxIndex);
    const float* Found = HebbianWeights.Find(Key);
    return Found ? *Found : 0.0f;
}

void USoulUnificationComponent::DrawConnections() const
{
    if (!GetWorld() || Souls.Num() == 0)
    {
        return;
    }

    for (const auto& Pair : HebbianWeights)
    {
        const int32 IndexA = Pair.Key.X;
        const int32 IndexB = Pair.Key.Y;
        if (!Souls.IsValidIndex(IndexA) || !Souls.IsValidIndex(IndexB))
        {
            continue;
        }

        const FSoulNode& SoulA = Souls[IndexA];
        const FSoulNode& SoulB = Souls[IndexB];
        const float Weight = Pair.Value;
        const FLinearColor Color = FLinearColor::LerpUsingHSV(SoulA.SoulColor, SoulB.SoulColor, 0.5f);

        DrawDebugLine(
            GetWorld(),
            SoulA.Position,
            SoulB.Position,
            Color.ToFColor(true),
            false,
            ConnectionLifetime,
            0,
            Weight * 5.0f);
    }
}
