// 4-qubit hyperflux capacitance simulator (conceptual)
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <complex>
#include "QuantumHyperfluxComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UQuantumHyperfluxComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuantumHyperfluxComponent();

    virtual void BeginPlay() override;

    // Reset to |0000> and clear prepared states
    UFUNCTION(BlueprintCallable, Category = "Quantum|State")
    void ResetState();

    // Prepare |psi1> with RY(α,β,γ,δ) and optional entanglement (CZ 0-1, 2-3)
    UFUNCTION(BlueprintCallable, Category = "Quantum|State")
    void PreparePsi1(float Alpha, float Beta, float Gamma, float Delta, bool bEntanglePairs = true);

    // Prepare |psi2> with X on q0,q1 then RY(ε,ζ,η,θ) and optional entanglement (CZ 0-1, 2-3)
    UFUNCTION(BlueprintCallable, Category = "Quantum|State")
    void PreparePsi2(float Epsilon, float Zeta, float Eta, float Theta, bool bEntanglePairs = true);

    // Set superposition weights (complex), normalizes internally; builds |Psi> = c1|psi1> + c2|psi2>
    UFUNCTION(BlueprintCallable, Category = "Quantum|State")
    void SetSuperpositionWeights(float C1Real, float C1Imag, float C2Real, float C2Imag);

    // Optional classical sync: measure parity of q0,q1 and correct if both are 1 (X on both)
    UFUNCTION(BlueprintCallable, Category = "Quantum|Sync")
    void SynchronizeBinary(bool bApplyCorrection = true);

    // Compute effective capacitance C_eff based on approximation <cos(phi_i)> ~ cos(2π Φ_i/Φ0) * (A0 + A1 * <Z_i>)
    UFUNCTION(BlueprintCallable, Category = "Quantum|Capacitance")
    double ComputeEffectiveCapacitance();

    // Convenience: get <Z_i> for i in [0,3]
    UFUNCTION(BlueprintCallable, Category = "Quantum|Observables")
    TArray<double> GetZExpectations() const;

    // Accessors for current C_eff and parity expectation
    UPROPERTY(BlueprintReadOnly, Category = "Quantum|Capacitance")
    double EffectiveCapacitance = 0.0;

    UPROPERTY(BlueprintReadOnly, Category = "Quantum|Sync")
    double ParityExpectation01 = 0.0; // <Z0 Z1>

    // Model parameters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Capacitance")
    double C0 = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Capacitance")
    double C1 = 1.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Capacitance")
    double C2 = 0.0;

    // Flux normalization and per-qubit flux Φ_i (same units as Φ0)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Capacitance")
    double Phi0 = 1.0; // set to 1 for normalized units

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Capacitance")
    TArray<double> FluxPhi; // size 4

    // Mapping <cos(phi_i)> ≈ cos(2π Φ_i/Φ0) * (A0 + A1 * <Z_i>)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Capacitance")
    double A0 = 0.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Capacitance")
    double A1 = 1.0;

    // Demo logging
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Debug")
    bool bLog = true;

    // Feature-map encoding of hyperdimensions -> 4-qubit PQC
    UFUNCTION(BlueprintCallable, Category = "Quantum|Encoding")
    void PrepareFromFeatureMap(const TArray<double>& Features, int32 Layers = 3, bool bEntanglePairs = true, double AngleScale = 1.0);

    // Phase locking via spin-echo on selected qubits (e.g., [0,1,2,3])
    UFUNCTION(BlueprintCallable, Category = "Quantum|Locking")
    void PhaseLockSpinEcho(const TArray<int32>& Qubits);

    // Use projector-based hyperstate operator with K synthetic hyperstates
    UFUNCTION(BlueprintCallable, Category = "Quantum|Hyperstates")
    void GenerateHyperstates(int32 K = 1000, int32 Seed = 4242, bool bRandomLambdas = true);

    UFUNCTION(BlueprintCallable, Category = "Quantum|Hyperstates")
    double ComputeHyperstateCapacitanceOperator();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Hyperstates")
    bool bUseHyperstateOperator = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Hyperstates")
    bool bLogHyperstate = false;

private:
    using Cx = std::complex<double>;

    // State vector utilities (4 qubits -> 16 amplitudes)
    void ResizeState();
    void Normalize(TArray<Cx>& Vec) const;
    static int32 BasisSize() { return 16; }
    static FORCEINLINE bool Bit(int32 StateIndex, int32 Qubit) { return ((StateIndex >> Qubit) & 1) != 0; }

    // Apply gates to the given vector in-place
    void ApplyRy(TArray<Cx>& Vec, int32 Qubit, double Theta) const;
    void ApplyX(TArray<Cx>& Vec, int32 Qubit) const;
    void ApplyCZ(TArray<Cx>& Vec, int32 QubitA, int32 QubitB) const;

    // Observables
    double ExpectZ(const TArray<Cx>& Vec, int32 Qubit) const;
    double ExpectZZ(const TArray<Cx>& Vec, int32 QubitA, int32 QubitB) const;

    // Helpers for encoding and echo
    void ApplySpinEcho(TArray<Cx>& Vec, int32 Qubit) const;
    double HashSignAggregate(const TArray<double>& Features, int32 Qubit, int32 Layer, int32 Seed, double AngleScale) const;

private:
    TArray<Cx> Psi1; // prepared |psi1>
    TArray<Cx> Psi2; // prepared |psi2>
    TArray<Cx> Psi;  // superposition

    Cx C1Weight = Cx(1.0, 0.0);
    Cx C2Weight = Cx(0.0, 0.0);

    // Synthetic hyperstates (not UPROPERTY)
    TArray<TArray<Cx>> Hyperstates;
    TArray<double> HyperLambdas;
};
