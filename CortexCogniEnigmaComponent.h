// Converted from Unity CortexCogniEnigma MonoBehaviour to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CortexCogniEnigmaComponent.generated.h"

class AActor;
class UMaterialInstanceDynamic;
class UPrimitiveComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCortexCogniEnigmaComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCortexCogniEnigmaComponent();

    /** Source used for environmental awareness */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cortex")
    AActor* EnvironmentSource = nullptr;

    /** Detection radius */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cortex", meta=(ClampMin=0.0f))
    float DetectionRadius = 500.0f;

    /** Colors used to visualize activation */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cortex")
    FLinearColor ActiveColor = FLinearColor(0.f, 1.f, 1.f, 1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cortex")
    FLinearColor DormantColor = FLinearColor::Gray;

    /** Adaptation threshold */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cortex", meta=(ClampMin=0.0f, ClampMax=2.0f))
    float AdaptationThreshold = 0.5f;

    /** Polling interval */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cortex", meta=(ClampMin=0.01f))
    float AnalysisInterval = 1.0f;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    TMap<FString, float> NeuralPathways;
    TArray<FString> Memory;
    FTimerHandle AnalysisTimerHandle;
    UPROPERTY()
    UMaterialInstanceDynamic* DynamicMaterial = nullptr;
    UPROPERTY()
    UPrimitiveComponent* TargetRenderer = nullptr;

    void InitializeRenderer();
    void AnalyzeEnvironment();
    FString DetectStimuli() const;
    void ProcessStimuli(const FString& Stimuli);
    void Adapt(const FString& Stimuli);
    void UpdateAppearance(float Intensity);
};
