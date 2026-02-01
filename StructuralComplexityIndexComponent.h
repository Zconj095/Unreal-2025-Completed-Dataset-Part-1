#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructuralComplexityIndexComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStructuralComplexityIndexComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStructuralComplexityIndexComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="SCI Parameters")
    int32 NumberOfNeurons = 1000;

    UPROPERTY(EditAnywhere, Category="SCI Parameters")
    float NeuralConnectivity = 1.0f;

    UPROPERTY(EditAnywhere, Category="SCI Parameters")
    int32 SpecializedBrainRegions = 1;

    UPROPERTY(EditAnywhere, Category="SCI Parameters")
    float Alpha = 1.0f;

    UPROPERTY(EditAnywhere, Category="SCI Parameters")
    float Beta = 1.0f;

    float CalculateSCI() const;
};
