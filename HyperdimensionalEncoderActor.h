// Actor demonstration: encode ~1000 hyperdimensions into 4-qubit PQC and compute C_eff
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuantumHyperfluxComponent.h"
#include "HyperdimensionalEncoderActor.generated.h"

UCLASS()
class PEKBGGAP_API AHyperdimensionalEncoderActor : public AActor
{
    GENERATED_BODY()

public:
    AHyperdimensionalEncoderActor();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quantum")
    UQuantumHyperfluxComponent* QuantumComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Encoding")
    int32 FeatureCount = 1000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Encoding")
    int32 EncodingLayers = 3;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Encoding")
    double AngleScale = 1.0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Locking")
    bool bApplySpinEcho = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Hyperstates")
    int32 HyperstatesK = 1000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum|Hyperstates")
    int32 HyperstateSeed = 4242;
};
