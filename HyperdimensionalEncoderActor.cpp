#include "HyperdimensionalEncoderActor.h"

AHyperdimensionalEncoderActor::AHyperdimensionalEncoderActor()
{
    PrimaryActorTick.bCanEverTick = false;
    QuantumComponent = CreateDefaultSubobject<UQuantumHyperfluxComponent>(TEXT("QuantumComponent"));
}

void AHyperdimensionalEncoderActor::BeginPlay()
{
    Super::BeginPlay();

    if (!QuantumComponent) { return; }

    // Generate synthetic 1000-dim features: mix of sinusoids and noise
    TArray<double> X; X.SetNum(FMath::Max(1, FeatureCount));
    for (int32 j = 0; j < X.Num(); ++j)
    {
        const double t = (double)j / (double)X.Num();
        const double s = FMath::Sin(2.0 * PI * 3.0 * t) + 0.5 * FMath::Cos(2.0 * PI * 7.0 * t);
        const double n = (FMath::FRand() - 0.5) * 0.1; // small noise
        X[j] = s + n;
    }

    // Encode into 4-qubit state via PQC
    QuantumComponent->PrepareFromFeatureMap(X, EncodingLayers, /*bEntanglePairs*/ true, AngleScale);

    // Optional spin-echo on all qubits to phase-lock
    if (bApplySpinEcho)
    {
        QuantumComponent->PhaseLockSpinEcho({0,1,2,3});
    }

    // Option A: flux-based capacitance surrogate
    QuantumComponent->FluxPhi = { 0.12, 0.34, 0.56, 0.78 };
    QuantumComponent->Phi0 = 1.0;
    QuantumComponent->C0 = 0.0; QuantumComponent->C1 = 1.0; QuantumComponent->C2 = 0.1;
    const double CEffFlux = QuantumComponent->ComputeEffectiveCapacitance();
    UE_LOG(LogTemp, Log, TEXT("C_eff (flux surrogate) = %.6f"), CEffFlux);

    // Option B: projector-based hyperstate operator (1000 hyperstates)
    QuantumComponent->bUseHyperstateOperator = true;
    QuantumComponent->bLogHyperstate = true;
    QuantumComponent->GenerateHyperstates(HyperstatesK, HyperstateSeed, /*bRandomLambdas*/ true);
    const double CEffOp = QuantumComponent->ComputeHyperstateCapacitanceOperator();
    UE_LOG(LogTemp, Log, TEXT("C_eff (hyperstate operator, K=%d) = %.6f"), HyperstatesK, CEffOp);
}
