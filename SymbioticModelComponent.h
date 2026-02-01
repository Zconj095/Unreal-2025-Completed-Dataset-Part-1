#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SymbioticModelComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USymbioticModelComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USymbioticModelComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Symbiosis")
    float EfficiencyConstant = 1.5f;

    UPROPERTY(EditAnywhere, Category="Symbiosis")
    float ResourceA = 100.0f;

    UPROPERTY(EditAnywhere, Category="Symbiosis")
    float ResourceB = 80.0f;

    void EvaluateBenefit() const;
};
