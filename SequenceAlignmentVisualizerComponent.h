#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SequenceAlignmentVisualizerComponent.generated.h"

class AActor;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USequenceAlignmentVisualizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USequenceAlignmentVisualizerComponent();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Alignment")
    FString SequenceA = TEXT("ACGTC");

    UPROPERTY(EditAnywhere, Category="Alignment")
    FString SequenceB = TEXT("ACTC");

    UPROPERTY(EditAnywhere, Category="Alignment")
    int32 MatchScore = 2;

    UPROPERTY(EditAnywhere, Category="Alignment")
    int32 GapPenalty = 1;

    UPROPERTY(EditAnywhere, Category="Visualization")
    float HorizontalSpacing = 200.0f;

    UPROPERTY(EditAnywhere, Category="Visualization")
    TSubclassOf<AActor> MatchActor;

    UPROPERTY(EditAnywhere, Category="Visualization")
    TSubclassOf<AActor> GapActor;

    void VisualizeAlignment() const;
};
