#pragma once

#include "CoreMinimal.h"
#include "ElementalTypeTwo.h"
#include "QuantumElementTwo.h" // For FComplexSimple
#include "QuantumElementThree.generated.h"

USTRUCT(BlueprintType)
struct PEKBGGAP_API FElementConnection
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
    int32 TargetIndex = INDEX_NONE; // Index into owning field array

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
    float Probability = 0.f; // 0..1 weight
};

USTRUCT(BlueprintType)
struct PEKBGGAP_API FQuantumElementThree
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FVector Position = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float EnergyLevel = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FComplexSimple ProbabilityWaveFunction; // Simple complex value

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FVector HyperDimensionalCoordXYZ = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float HyperDimensionalCoordW = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Elemental")
    EElementalTypeTwo ElementalAttribute = EElementalTypeTwo::Fire;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Elemental")
    float ElementalIntensity = 1.f;

    // Possibility network connections
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Network")
    TArray<FElementConnection> PossibleConnections;

    void AddConnection(int32 TargetIdx, float Probability)
    {
        if (TargetIdx == INDEX_NONE) return;
        FElementConnection Conn; Conn.TargetIndex = TargetIdx; Conn.Probability = FMath::Clamp(Probability, 0.f, 1.f);
        PossibleConnections.Add(Conn);
    }

    void ClearConnections()
    {
        PossibleConnections.Reset();
    }

    // Mirror of Unity API: Transition the element's quantum state
    void TransitionState(const FComplexSimple& NewWaveFunc, float TimeDelta)
    {
        const float T = FMath::Clamp(TimeDelta, 0.f, 1.f);
        ProbabilityWaveFunction = FComplexSimple::Lerp(ProbabilityWaveFunction, NewWaveFunc, T);
    }

    // Mirror of Unity API: iterate connections and apply transitions probabilistically
    void TransitionBasedOnNetwork(float DeltaTime, const TArray<FQuantumElementThree>& Field)
    {
        for (const FElementConnection& Connection : PossibleConnections)
        {
            if (!Field.IsValidIndex(Connection.TargetIndex))
            {
                continue;
            }
            if (FMath::FRand() < Connection.Probability)
            {
                const FComplexSimple& TargetWave = Field[Connection.TargetIndex].ProbabilityWaveFunction;
                TransitionState(TargetWave, DeltaTime);
            }
        }
    }
};
