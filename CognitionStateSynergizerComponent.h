// Converted from Unity MonoBehaviour to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitionStateSynergizerComponent.generated.h"

USTRUCT(BlueprintType)
struct FCoreCognitiveState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive State")
    FString Name = TEXT("State");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive State", meta=(ClampMin=0.0f, ClampMax=1.0f))
    float Intensity = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive State")
    FLinearColor StateColor = FLinearColor::White;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitionStateSynergizerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCognitionStateSynergizerComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Fusion")
    TArray<FCoreCognitiveState> CognitiveStates;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Fusion")
    FLinearColor SynergizedColor = FLinearColor::Black;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Fusion", meta=(ClampMin=0.0f, ClampMax=1.0f))
    float SynergizedIntensity = 0.0f;

    UFUNCTION(BlueprintCallable, Category="Cognitive Fusion")
    void SynergizeStates();

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void InitializeExampleStates();
    void UpdateVisualization();
    void SpawnVisualizationSphere();
};
