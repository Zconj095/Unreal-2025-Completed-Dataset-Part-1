#include "StructuralAnalysis2Component.h"

#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

UStructuralAnalysis2Component::UStructuralAnalysis2Component()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UStructuralAnalysis2Component::BeginPlay()
{
    Super::BeginPlay();

    InitializeFields();
    const double AlignmentIndex = ComputeAlignmentIndex();
    UE_LOG(LogTemp, Log, TEXT("Alignment Index (A): %.6f"), AlignmentIndex);
}

void UStructuralAnalysis2Component::InitializeFields()
{
    const int32 Resolution = FMath::Max(2, GridResolution);
    const int32 TotalSize = Resolution * Resolution * Resolution;

    NeuralDensity.Init(0.0, TotalSize);
    MagicalEnergyField.Init(0.0, TotalSize);

    for (int32 Index = 0; Index < TotalSize; ++Index)
    {
        NeuralDensity[Index] = FMath::FRand();
        MagicalEnergyField[Index] = FMath::FRand();
    }
}

double UStructuralAnalysis2Component::ComputeAlignmentIndex() const
{
    const int32 Resolution = FMath::Max(2, GridResolution);
    double Numerator = 0.0;
    double Denominator = 0.0;

    for (int32 X = 1; X < Resolution - 1; ++X)
    {
        for (int32 Y = 1; Y < Resolution - 1; ++Y)
        {
            for (int32 Z = 1; Z < Resolution - 1; ++Z)
            {
                const FVector GradN = ComputeGradient(NeuralDensity, X, Y, Z);
                const FVector GradPhi = ComputeGradient(MagicalEnergyField, X, Y, Z);

                Numerator += FVector::DotProduct(GradN, GradPhi);
                Denominator += GradN.Size();
            }
        }
    }

    return Denominator > KINDA_SMALL_NUMBER ? (Numerator / Denominator) : 0.0;
}

FVector UStructuralAnalysis2Component::ComputeGradient(const TArray<double>& Field, int32 X, int32 Y, int32 Z) const
{
    const double Dx = (Field[ToFlatIndex(X + 1, Y, Z)] - Field[ToFlatIndex(X - 1, Y, Z)]) * 0.5;
    const double Dy = (Field[ToFlatIndex(X, Y + 1, Z)] - Field[ToFlatIndex(X, Y - 1, Z)]) * 0.5;
    const double Dz = (Field[ToFlatIndex(X, Y, Z + 1)] - Field[ToFlatIndex(X, Y, Z - 1)]) * 0.5;

    return FVector(Dx, Dy, Dz);
}

int32 UStructuralAnalysis2Component::ToFlatIndex(int32 X, int32 Y, int32 Z) const
{
    const int32 Resolution = FMath::Max(2, GridResolution);
    return X + Y * Resolution + Z * Resolution * Resolution;
}
