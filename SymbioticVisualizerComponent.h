#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SymbioticVisualizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USymbioticVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USymbioticVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Symbiosis")
    TSubclassOf<AActor> Species1ActorClass;

    UPROPERTY(EditAnywhere, Category="Symbiosis")
    TSubclassOf<AActor> Species2ActorClass;

    UPROPERTY(EditAnywhere, Category="Symbiosis")
    float EfficiencyConstant = 1.5f;

    UPROPERTY(EditAnywhere, Category="Symbiosis")
    float Resource1 = 100.0f;

    UPROPERTY(EditAnywhere, Category="Symbiosis")
    float Resource2 = 80.0f;

    void VisualizeResources();
    double CalculateBenefit() const;
};
