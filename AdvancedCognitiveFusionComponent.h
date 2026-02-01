// Converted from Unity MonoBehaviour AdvancedCognitiveFusionSimulator to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "AdvancedCognitiveFusionComponent.generated.h"

class UStaticMeshComponent;

USTRUCT(BlueprintType)
struct FCognitiveState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive State")
    FString Name = TEXT("State");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive State", meta=(ClampMin=0.0f, ClampMax=1.0f))
    float Intensity = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive State")
    FVector EmotionVector = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive State")
    FLinearColor StateColor = FLinearColor::White;
};

USTRUCT(BlueprintType)
struct FFusedState
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Fusion")
    FVector FusedVector = FVector::ZeroVector;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Fusion", meta=(ClampMin=0.0f, ClampMax=1.0f))
    float OverallIntensity = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Fusion")
    FLinearColor BlendedColor = FLinearColor::Black;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UAdvancedCognitiveFusionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAdvancedCognitiveFusionComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cognitive Fusion")
    TArray<FCognitiveState> CognitiveStates;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cognitive Fusion")
    FFusedState FusedCognitiveState;

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
