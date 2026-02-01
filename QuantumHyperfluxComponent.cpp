#include "QuantumHyperfluxComponent.h"

UQuantumHyperfluxComponent::UQuantumHyperfluxComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    FluxPhi.SetNum(4);
    ResizeState();
}

void UQuantumHyperfluxComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UQuantumHyperfluxComponent::ResizeState()
{
    Psi1.Init(Cx(0.0, 0.0), BasisSize());
    Psi2.Init(Cx(0.0, 0.0), BasisSize());
    Psi.Init(Cx(0.0, 0.0), BasisSize());
}

void UQuantumHyperfluxComponent::Normalize(TArray<Cx>& Vec) const
{
    long double Sum = 0.0L;
    for (const Cx& a : Vec) { Sum += std::norm(a); }
    if (Sum <= 0.0L) { return; }
    const long double Inv = 1.0L / std::sqrt(Sum);
    for (Cx& a : Vec) { a *= Inv; }
}

void UQuantumHyperfluxComponent::ResetState()
{
    ResizeState();
    Psi1[0] = Cx(1.0, 0.0);
    Psi2[0] = Cx(1.0, 0.0);
    Psi[0]  = Cx(1.0, 0.0);
    C1Weight = Cx(1.0, 0.0);
    C2Weight = Cx(0.0, 0.0);
    EffectiveCapacitance = 0.0;
    ParityExpectation01 = 0.0;
}

void UQuantumHyperfluxComponent::ApplyRy(TArray<Cx>& Vec, int32 Qubit, double Theta) const
{
    const double c = std::cos(Theta * 0.5);
    const double s = std::sin(Theta * 0.5);
    const int32 N = BasisSize();
    const int32 Mask = (1 << Qubit);
    for (int32 i = 0; i < N; ++i)
    {
        if ((i & Mask) == 0)
        {
            const int32 j = i | Mask; // flip bit
            const Cx a = Vec[i];
            const Cx b = Vec[j];
            // [c -s; s c] * [a; b]
            Vec[i] = Cx(c) * a - Cx(s) * b;
            Vec[j] = Cx(s) * a + Cx(c) * b;
        }
    }
}

void UQuantumHyperfluxComponent::ApplyX(TArray<Cx>& Vec, int32 Qubit) const
{
    const int32 N = BasisSize();
    const int32 Mask = (1 << Qubit);
    for (int32 i = 0; i < N; ++i)
    {
        if ((i & Mask) == 0)
        {
            const int32 j = i | Mask; // partner with bit flipped
            const Cx a = Vec[i];
            Vec[i] = Vec[j];
            Vec[j] = a;
        }
    }
}

void UQuantumHyperfluxComponent::ApplyCZ(TArray<Cx>& Vec, int32 QubitA, int32 QubitB) const
{
    const int32 N = BasisSize();
    const int32 MaskA = (1 << QubitA);
    const int32 MaskB = (1 << QubitB);
    for (int32 i = 0; i < N; ++i)
    {
        if ((i & MaskA) && (i & MaskB))
        {
            Vec[i] = -Vec[i];
        }
    }
}

double UQuantumHyperfluxComponent::ExpectZ(const TArray<Cx>& Vec, int32 Qubit) const
{
    const int32 N = BasisSize();
    const int32 Mask = (1 << Qubit);
    long double E = 0.0L;
    for (int32 i = 0; i < N; ++i)
    {
        const long double p = std::norm(Vec[i]);
        const int32 bit = (i & Mask) ? 1 : 0;
        E += (bit ? -p : +p); // |0> -> +1, |1> -> -1
    }
    return static_cast<double>(E);
}

double UQuantumHyperfluxComponent::ExpectZZ(const TArray<Cx>& Vec, int32 QubitA, int32 QubitB) const
{
    const int32 N = BasisSize();
    const int32 MaskA = (1 << QubitA);
    const int32 MaskB = (1 << QubitB);
    long double E = 0.0L;
    for (int32 i = 0; i < N; ++i)
    {
        const long double p = std::norm(Vec[i]);
        const int sA = ((i & MaskA) ? -1 : +1);
        const int sB = ((i & MaskB) ? -1 : +1);
        E += p * (sA * sB);
    }
    return static_cast<double>(E);
}

void UQuantumHyperfluxComponent::PreparePsi1(float Alpha, float Beta, float Gamma, float Delta, bool bEntanglePairs)
{
    Psi1.Init(Cx(0.0, 0.0), BasisSize());
    Psi1[0] = Cx(1.0, 0.0);
    ApplyRy(Psi1, 0, Alpha);
    ApplyRy(Psi1, 1, Beta);
    ApplyRy(Psi1, 2, Gamma);
    ApplyRy(Psi1, 3, Delta);
    if (bEntanglePairs)
    {
        ApplyCZ(Psi1, 0, 1);
        ApplyCZ(Psi1, 2, 3);
    }
    Normalize(Psi1);
}

void UQuantumHyperfluxComponent::PreparePsi2(float Epsilon, float Zeta, float Eta, float Theta, bool bEntanglePairs)
{
    Psi2.Init(Cx(0.0, 0.0), BasisSize());
    Psi2[0] = Cx(1.0, 0.0);
    // X on q0, q1
    ApplyX(Psi2, 0);
    ApplyX(Psi2, 1);
    // RY rotations
    ApplyRy(Psi2, 0, Epsilon);
    ApplyRy(Psi2, 1, Zeta);
    ApplyRy(Psi2, 2, Eta);
    ApplyRy(Psi2, 3, Theta);
    if (bEntanglePairs)
    {
        ApplyCZ(Psi2, 0, 1);
        ApplyCZ(Psi2, 2, 3);
    }
    Normalize(Psi2);
}

void UQuantumHyperfluxComponent::SetSuperpositionWeights(float C1Real, float C1Imag, float C2Real, float C2Imag)
{
    C1Weight = Cx(C1Real, C1Imag);
    C2Weight = Cx(C2Real, C2Imag);

    Psi.Init(Cx(0.0, 0.0), BasisSize());
    for (int32 i = 0; i < BasisSize(); ++i)
    {
        Psi[i] = C1Weight * Psi1[i] + Cx(C2Weight) * Psi2[i];
    }
    Normalize(Psi);
}

void UQuantumHyperfluxComponent::SynchronizeBinary(bool bApplyCorrection)
{
    // Compute parity expectation <Z0 Z1>
    ParityExpectation01 = ExpectZZ(Psi, 0, 1);
    if (!bApplyCorrection) { return; }

    // Simple deterministic branch: if P(|11>) > 0.5, apply X to q0 and q1
    long double P11 = 0.0L;
    for (int32 i = 0; i < BasisSize(); ++i)
    {
        if (Bit(i,0) && Bit(i,1)) { P11 += std::norm(Psi[i]); }
    }
    if (P11 > 0.5L)
    {
        ApplyX(Psi, 0);
        ApplyX(Psi, 1);
        Normalize(Psi);
        ParityExpectation01 = ExpectZZ(Psi, 0, 1);
    }
}

double UQuantumHyperfluxComponent::ComputeEffectiveCapacitance()
{
    // Compute <Z_i>
    double ZExp[4] = {0,0,0,0};
    for (int k = 0; k < 4; ++k) { ZExp[k] = ExpectZ(Psi, k); }

    // Compute <cos(phi_i)> via approximation cos(2π Φ_i/Φ0) * (A0 + A1 * <Z_i>)
    double SumCos = 0.0;
    const double TwoPi = 6.283185307179586;
    for (int i = 0; i < 4; ++i)
    {
        const double Phi = (i < FluxPhi.Num()) ? FluxPhi[i] : 0.0;
        const double CosBase = std::cos(TwoPi * (Phi0 != 0.0 ? (Phi / Phi0) : Phi));
        const double ExCos = CosBase * (A0 + A1 * ZExp[i]);
        SumCos += ExCos;
    }

    EffectiveCapacitance = C0 + C1 * SumCos + C2 * (SumCos * SumCos);

    if (bLog)
    {
        UE_LOG(LogTemp, Log, TEXT("Z-Expectations: [%.3f, %.3f, %.3f, %.3f], SumCos=%.3f, C_eff=%.6f"),
            ZExp[0], ZExp[1], ZExp[2], ZExp[3], SumCos, EffectiveCapacitance);
    }

    return EffectiveCapacitance;
}

TArray<double> UQuantumHyperfluxComponent::GetZExpectations() const
{
    TArray<double> Out; Out.SetNum(4);
    Out[0] = ExpectZ(Psi, 0);
    Out[1] = ExpectZ(Psi, 1);
    Out[2] = ExpectZ(Psi, 2);
    Out[3] = ExpectZ(Psi, 3);
    return Out;
}

// --- New: Feature-map encoding and phase locking ---

void UQuantumHyperfluxComponent::ApplySpinEcho(TArray<Cx>& Vec, int32 Qubit) const
{
    ApplyX(Vec, Qubit);
    ApplyRy(Vec, Qubit, PI); // RY(pi)
    ApplyX(Vec, Qubit);
}

static FORCEINLINE uint32 MixU32(uint32 x)
{
    x ^= x >> 16; x *= 0x7feb352d; x ^= x >> 15; x *= 0x846ca68b; x ^= x >> 16; return x;
}

double UQuantumHyperfluxComponent::HashSignAggregate(const TArray<double>& Features, int32 Qubit, int32 Layer, int32 Seed, double AngleScale) const
{
    const int32 N = Features.Num();
    if (N <= 0) { return 0.0; }
    long double Sum = 0.0L;
    const uint32 base = MixU32((uint32)Seed ^ (uint32)(Qubit * 73856093) ^ (uint32)(Layer * 19349663));
    for (int32 j = 0; j < N; ++j)
    {
        uint32 h = MixU32(base ^ (uint32)j * 0x9e3779b9u);
        const int s = (h & 1u) ? +1 : -1; // random sign
        Sum += (long double)s * (long double)Features[j];
    }
    // squash to [-pi, pi]
    const double theta = AngleScale * std::atan((double)Sum);
    return theta;
}

void UQuantumHyperfluxComponent::PrepareFromFeatureMap(const TArray<double>& Features, int32 Layers, bool bEntanglePairs, double AngleScale)
{
    Psi.Init(Cx(0.0, 0.0), BasisSize());
    Psi[0] = Cx(1.0, 0.0);

    const int32 L = FMath::Max(1, Layers);
    const int32 Seed = 1337;
    for (int32 l = 0; l < L; ++l)
    {
        const double t0 = HashSignAggregate(Features, 0, l, Seed, AngleScale);
        const double t1 = HashSignAggregate(Features, 1, l, Seed, AngleScale);
        const double t2 = HashSignAggregate(Features, 2, l, Seed, AngleScale);
        const double t3 = HashSignAggregate(Features, 3, l, Seed, AngleScale);

        ApplyRy(Psi, 0, t0);
        ApplyRy(Psi, 1, t1);
        ApplyRy(Psi, 2, t2);
        ApplyRy(Psi, 3, t3);

        if (bEntanglePairs)
        {
            ApplyCZ(Psi, 0, 1);
            ApplyCZ(Psi, 2, 3);
        }
    }
    Normalize(Psi);
}

void UQuantumHyperfluxComponent::PhaseLockSpinEcho(const TArray<int32>& Qubits)
{
    for (int32 q : Qubits)
    {
        if (q >= 0 && q < 4)
        {
            ApplySpinEcho(Psi, q);
        }
    }
    Normalize(Psi);
}

// --- New: Projector-based hyperstate operator ---

void UQuantumHyperfluxComponent::GenerateHyperstates(int32 K, int32 Seed, bool bRandomLambdas)
{
    Hyperstates.Empty();
    HyperLambdas.Empty();
    Hyperstates.Reserve(K);
    HyperLambdas.Reserve(K);

    // Simple PRNG
    uint32 s = (uint32)Seed;
    auto NextRand = [&s]() -> double {
        s = s * 1664525u + 1013904223u;
        return (double)(s) / (double)UINT32_MAX; // [0,1]
    };

    for (int32 k = 0; k < K; ++k)
    {
        TArray<Cx> Phi; Phi.Init(Cx(0.0, 0.0), BasisSize());
        Phi[0] = Cx(1.0, 0.0);
        // Random shallow PQC
        for (int l = 0; l < 2; ++l)
        {
            ApplyRy(Phi, 0, (NextRand()*2-1) * PI);
            ApplyRy(Phi, 1, (NextRand()*2-1) * PI);
            ApplyRy(Phi, 2, (NextRand()*2-1) * PI);
            ApplyRy(Phi, 3, (NextRand()*2-1) * PI);
            if (NextRand() > 0.5) ApplyCZ(Phi, 0, 1);
            if (NextRand() > 0.5) ApplyCZ(Phi, 2, 3);
        }
        Normalize(Phi);
        Hyperstates.Add(MoveTemp(Phi));
        const double lambda = bRandomLambdas ? (0.5 + NextRand()) : 1.0; // ~[0.5,1.5]
        HyperLambdas.Add(lambda);
    }

    if (bLogHyperstate)
    {
        UE_LOG(LogTemp, Log, TEXT("Generated %d hyperstates for operator."), K);
    }
}

double UQuantumHyperfluxComponent::ComputeHyperstateCapacitanceOperator()
{
    if (Hyperstates.Num() == 0) { return 0.0; }
    long double CE = 0.0L;
    for (int32 k = 0; k < Hyperstates.Num(); ++k)
    {
        const TArray<Cx>& Phi = Hyperstates[k];
        // overlap <phi|psi>
        Cx dot(0.0, 0.0);
        for (int32 i = 0; i < BasisSize(); ++i)
        {
            dot += std::conj(Phi[i]) * Psi[i];
        }
        const long double pk = std::norm(dot);
        CE += (long double)HyperLambdas[k] * pk;
    }
    EffectiveCapacitance = (double)CE;
    if (bLogHyperstate)
    {
        UE_LOG(LogTemp, Log, TEXT("C_eff (hyperstate operator) = %.6f"), EffectiveCapacitance);
    }
    return EffectiveCapacitance;
}
