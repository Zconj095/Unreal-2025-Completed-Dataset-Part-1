#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructuralAnalysis2Component.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStructuralAnalysis2Component : public UActorComponent
{
    GENERATED_BODY()

public:
    UStructuralAnalysis2Component();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Structural Analysis", meta=(ClampMin="2"))
    int32 GridResolution = 10;

    TArray<double> NeuralDensity;
    TArray<double> MagicalEnergyField;

    void InitializeFields();
    double ComputeAlignmentIndex() const;
    FVector ComputeGradient(const TArray<double>& Field, int32 X, int32 Y, int32 Z) const;
    FORCEINLINE int32 ToFlatIndex(int32 X, int32 Y, int32 Z) const;
};
