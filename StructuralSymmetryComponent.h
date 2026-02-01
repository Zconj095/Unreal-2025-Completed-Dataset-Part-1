#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StructuralSymmetryComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UStructuralSymmetryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UStructuralSymmetryComponent();

protected:
    virtual void BeginPlay() override;
    virtual void OnComponentCreated() override;

private:
    UPROPERTY(EditAnywhere, Category="Symmetry")
    int32 NumStructures = 10;

    UPROPERTY(EditAnywhere, Category="Visualization")
    TSubclassOf<AActor> SphereActorClass;

    TArray<float> LeftStructures;
    TArray<float> RightStructures;

    void InitializeStructures();
    float CalculateSymmetryIndex() const;
    void VisualizeStructures() const;
};
