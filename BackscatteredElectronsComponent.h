// Converted from Unity MonoBehaviour to Unreal ActorComponent for simulating backscattered electrons.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "BackscatteredElectronsComponent.generated.h"

class UTexture2D;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UBackscatteredElectronsComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBackscatteredElectronsComponent();

    /** Maximum detection angle before the intensity is zeroed. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Backscattered")
    float MaxDetectionAngle = 90.0f;

    /** Scalar applied to material atomic number to get final intensity. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Backscattered")
    float IntensityMultiplier = 1.0f;

    /** Resolution of the detection grid. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Backscattered", meta=(ClampMin=1))
    int32 Resolution = 256;

    /** Distance used for the BSE ray trace. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Backscattered")
    float TraceDistance = 1000.0f;

    /** Plane size (world units) used to project the detection grid. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Backscattered")
    FVector2D CaptureSize = FVector2D(10.0f, 10.0f);

    /** Collision channel used when tracing for sample geometry. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Backscattered")
    TEnumAsByte<ECollisionChannel> TraceChannel = ECC_WorldStatic;

    /** Should the component run the simulation every tick? */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Backscattered")
    bool bAutoSimulate = true;

    /** The generated texture representing BSE intensity. */
    UPROPERTY(BlueprintReadOnly, Category="Backscattered")
    UTexture2D* BseTexture = nullptr;

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

private:
    void CreateBseTexture();
    void SimulateBackscatteredElectrons();
    void UpdateTexture();

    TArray<FColor> PixelBuffer;
};
