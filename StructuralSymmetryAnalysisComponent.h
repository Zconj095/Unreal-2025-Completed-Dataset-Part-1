#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructuralSymmetryAnalysisComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStructuralSymmetryAnalysisComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStructuralSymmetryAnalysisComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Symmetry")
    int32 NumberOfStructures = 5;

    UPROPERTY(EditAnywhere, Category="Symmetry")
    TSubclassOf<AActor> SphereActorClass;

    TArray<float> LeftStructures;
    TArray<float> RightStructures;

    void InitializeStructures();
    float CalculateSymmetryIndex() const;
    void VisualizeStructures() const;
};
