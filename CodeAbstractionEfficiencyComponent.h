// Copyright ...
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CodeAbstractionEfficiencyComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UCodeAbstractionEfficiencyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCodeAbstractionEfficiencyComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abstraction")
	float Beta = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abstraction")
	float NeuronsAbstract = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Abstraction", meta=(ClampMin="0.01"))
	float NeuronsTotal = 1.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Abstraction")
	float CAE = 0.0f;

	UFUNCTION(BlueprintCallable, Category="Abstraction")
	void UpdateBeta(float NewBeta);

	UFUNCTION(BlueprintCallable, Category="Abstraction")
	void UpdateNeuronsAbstract(float NewNeurons);

	UFUNCTION(BlueprintCallable, Category="Abstraction")
	void UpdateNeuronsTotal(float NewTotal);
};
