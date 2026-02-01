#include "QuantumHyperfluxActor.h"

AQuantumHyperfluxActor::AQuantumHyperfluxActor()
{
    PrimaryActorTick.bCanEverTick = false;
    QuantumComponent = CreateDefaultSubobject<UQuantumHyperfluxComponent>(TEXT("QuantumComponent"));
}

void AQuantumHyperfluxActor::BeginPlay()
{
    Super::BeginPlay();

    if (!QuantumComponent) { return; }

    // Example: set some fluxes (normalized units)
    QuantumComponent->FluxPhi = { 0.10, 0.25, 0.40, 0.05 };
    QuantumComponent->Phi0 = 1.0; // normalized
    QuantumComponent->C0 = 0.0; QuantumComponent->C1 = 1.0; QuantumComponent->C2 = 0.2;
    QuantumComponent->A0 = 0.0; QuantumComponent->A1 = 1.0;

    // Prepare states
    QuantumComponent->PreparePsi1(Alpha, Beta, Gamma, Delta, bEntanglePairs);
    QuantumComponent->PreparePsi2(Epsilon, Zeta, Eta, Theta, bEntanglePairs);

    // Superposition
    QuantumComponent->SetSuperpositionWeights(C1Real, C1Imag, C2Real, C2Imag);

    // Optional binary synchronization (parity correction)
    if (bRunSync)
    {
        QuantumComponent->SynchronizeBinary(true);
    }

    // Compute and log effective capacitance
    const double CEff = QuantumComponent->ComputeEffectiveCapacitance();
    UE_LOG(LogTemp, Log, TEXT("Hyperflux C_eff = %.6f, Parity<Z0Z1>=%.3f"), CEff, QuantumComponent->ParityExpectation01);
}

