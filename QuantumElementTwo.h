#pragma once

#include "CoreMinimal.h"
#include "ElementalTypeTwo.h"
#include "QuantumElementTwo.generated.h"

USTRUCT(BlueprintType)
struct PEKBGGAP_API FComplexSimple
{
    GENERATED_BODY()

    FComplexSimple() = default;
    explicit FComplexSimple(float InReal, float InImag) : Real(InReal), Imag(InImag) {}

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float Real = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float Imag = 0.f;

    FORCEINLINE float MagnitudeSquared() const
    {
        return Real * Real + Imag * Imag;
    }

    static FORCEINLINE FComplexSimple Lerp(const FComplexSimple& A, const FComplexSimple& B, float T)
    {
        return FComplexSimple(FMath::Lerp(A.Real, B.Real, T), FMath::Lerp(A.Imag, B.Imag, T));
    }

    FORCEINLINE FString ToString() const
    {
        return FString::Printf(TEXT("(%g + %gi)"), Real, Imag);
    }

    FORCEINLINE FComplexSimple operator+(const FComplexSimple& Other) const
    {
        return FComplexSimple(Real + Other.Real, Imag + Other.Imag);
    }

    FORCEINLINE FComplexSimple operator*(const FComplexSimple& Other) const
    {
        return FComplexSimple(Real * Other.Real - Imag * Other.Imag, Real * Other.Imag + Imag * Other.Real);
    }
};

USTRUCT(BlueprintType)
struct PEKBGGAP_API FQuantumElementTwo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FVector Position = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float Energy = 0.f;

    // Simple complex wave function representation
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FComplexSimple WaveFunction;

    // 4D hyper coordinate stored as XYZ + W
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    FVector HyperCoordXYZ = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float HyperCoordW = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    EElementalTypeTwo ElementalAttribute = EElementalTypeTwo::Fire;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quantum")
    float ElementalIntensity = 1.f;

    // Behavioral methods mirroring the Unity example
    void TransitionState(const FComplexSimple& NewWaveFunction, float DeltaTime)
    {
        const float T = FMath::Clamp(DeltaTime, 0.f, 1.f);
        WaveFunction = FComplexSimple::Lerp(WaveFunction, NewWaveFunction, T);
    }

    float CalculateProbabilityDensity() const
    {
        return WaveFunction.MagnitudeSquared();
    }

    void InteractWith(FQuantumElementTwo& Other)
    {
        // Example rule set similar to Unity snippet
        if (ElementalAttribute == EElementalTypeTwo::Fire && Other.ElementalAttribute == EElementalTypeTwo::Water)
        {
            Energy -= Other.ElementalIntensity;
        }
        else if (ElementalAttribute == EElementalTypeTwo::Water && Other.ElementalAttribute == EElementalTypeTwo::Fire)
        {
            Energy += Other.ElementalIntensity;
        }
        // Additional rules can be added here as needed
        Energy = FMath::Max(0.f, Energy);
    }
};
