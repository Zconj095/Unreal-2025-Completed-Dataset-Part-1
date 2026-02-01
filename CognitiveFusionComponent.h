// Converted from Unity MonoBehaviour CognitiveFusionSimulator to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CognitiveFusionComponent.generated.h"

class UMaterialInstanceDynamic;
class UStaticMeshComponent;

USTRUCT(BlueprintType)
struct FCognitiveStateEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Fusion")
    FString Name = TEXT("State");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Fusion", meta=(ClampMin=0.0f, ClampMax=1.0f))
    float Intensity = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Fusion")
    FLinearColor StateColor = FLinearColor::White;
};

USTRUCT(BlueprintType)
struct FFusedCognitiveState
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Fusion")
    FString FusedName = TEXT("Fused Emotion State");

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Fusion", meta=(ClampMin=0.0f, ClampMax=1.0f))
    float CombinedIntensity = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Fusion")
    FLinearColor BlendedColor = FLinearColor::Black;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCognitiveFusionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCognitiveFusionComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Fusion")
    TArray<FCognitiveStateEntry> CognitiveStates;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Fusion")
    FFusedCognitiveState FusedCognitiveState;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void SimulateFusion();
    void UpdateVisualRepresentation();
    void EnsureVisualRepresentation();

    UPROPERTY(Transient)
    UStaticMeshComponent* VisualRepresentation = nullptr;

    UPROPERTY(Transient)
    UMaterialInstanceDynamic* DynamicMaterial = nullptr;
};
