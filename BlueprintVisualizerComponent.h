#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlueprintVisualizerComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UBlueprintVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBlueprintVisualizerComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** Size of the blueprint grid on one axis. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint Visualization", meta = (ClampMin = "1"))
	int32 GridDimension = 5;

	/** Threshold above which a cell is considered populated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint Visualization", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float VisualizationThreshold = 0.5f;

	/** Size of the debug cube (half extents). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint Visualization")
	float CubeSize = 25.0f;

	/** World spacing between grid cells. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint Visualization")
	float Spacing = 200.0f;

	/** Whether to draw debug visuals at runtime. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint Visualization")
	bool bDrawDebug = true;

	/** Compute blueprint array for the current parameters. */
	UFUNCTION(BlueprintCallable, Category = "Blueprint Visualization")
	TArray<float> GenerateBlueprint() const;

private:
	float SampleValue(int32 X, int32 Y, int32 Z) const;
	void DrawDebugVisualization(const TArray<float>& Blueprint) const;
};
