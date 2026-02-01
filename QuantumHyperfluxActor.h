// Demo actor that uses UQuantumHyperfluxComponent to showcase setup and C_eff
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuantumHyperfluxComponent.h"
#include "QuantumHyperfluxActor.generated.h"

UCLASS()
class PEKBGGAP_API AQuantumHyperfluxActor : public AActor
{
    GENERATED_BODY()

public:
    AQuantumHyperfluxActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quantum")
    UQuantumHyperfluxComponent* QuantumComponent;

    // Simple demo parameters
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Demo")
    float Alpha = 0.6f, Beta = 0.4f, Gamma = 0.9f, Delta = 0.3f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Demo")
    float Epsilon = 0.7f, Zeta = 0.2f, Eta = 0.5f, Theta = 0.8f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Demo")
    float C1Real = 0.8f, C1Imag = 0.0f, C2Real = 0.6f, C2Imag = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Demo")
    bool bEntanglePairs = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Demo")
    bool bRunSync = true;
};

