#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructuralAnalysisComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStructuralAnalysisComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStructuralAnalysisComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Structural")
    double Force = 1000.0;

    UPROPERTY(EditAnywhere, Category="Structural")
    double Area = 50.0;

    void EvaluateStress() const;
};
