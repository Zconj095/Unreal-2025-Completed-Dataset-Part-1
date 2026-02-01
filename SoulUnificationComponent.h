// Converted from Unity MonoBehaviour SoulUnificationWithHebbian to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SoulUnificationComponent.generated.h"

USTRUCT(BlueprintType)
struct FSoulNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul")
    FString Name = TEXT("Soul");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul", meta=(ClampMin=0.0f, ClampMax=1.0f))
    float Intensity = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul")
    FVector Position = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul")
    FLinearColor SoulColor = FLinearColor::White;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USoulUnificationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USoulUnificationComponent();

    /** Souls available for unification */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul Fusion")
    TArray<FSoulNode> Souls;

    /** Result of the latest unification */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Soul Fusion")
    FSoulNode UnifiedSoul;

    /** Auto-draw Hebbian connections every tick */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul Fusion")
    bool bAutoVisualizeConnections = true;

    /** How long each debug line will persist */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul Fusion")
    float ConnectionLifetime = 0.1f;

    UFUNCTION(BlueprintCallable, Category="Soul Fusion")
    void UnifySouls();

    UFUNCTION(BlueprintCallable, Category="Soul Fusion")
    void HebbianLearning(int32 SoulIndexA, int32 SoulIndexB, float Delta);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    TMap<FIntPoint, float> HebbianWeights;

    void InitializeHebbianWeights();
    void DrawConnections() const;
    float GetConnectionWeight(int32 A, int32 B) const;
};
