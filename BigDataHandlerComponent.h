// Converted from Unity MonoBehaviour BigDataHandlerSystem to Unreal ActorComponent.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BigDataHandlerComponent.generated.h"

class UQuantumHypervectorManagerComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UBigDataHandlerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBigDataHandlerComponent();

    UPROPERTY(BlueprintReadOnly, Category="Big Data")
    UQuantumHypervectorManagerComponent* QuantumManager = nullptr;

protected:
    virtual void BeginPlay() override;

private:
    void ActivateFoliage();
};
