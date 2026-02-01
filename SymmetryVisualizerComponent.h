#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SymmetryVisualizerComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USymmetryVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USymmetryVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Symmetry")
    TSubclassOf<AActor> PointActorClass;

    UPROPERTY(EditAnywhere, Category="Symmetry")
    FVector Position = FVector(1.0f, 0.0f, 0.0f);

    UPROPERTY(EditAnywhere, Category="Symmetry")
    FVector Axis = FVector(0.0f, 0.0f, 1.0f);

    UPROPERTY(EditAnywhere, Category="Symmetry")
    float AngleDegrees = 45.0f;

    void SpawnPoint(const FVector& Location) const;
};
