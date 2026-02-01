#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RunicCoreSector2Component.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API URunicCoreSector2Component : public UActorComponent
{
    GENERATED_BODY()

public:
    URunicCoreSector2Component();

protected:
    virtual void BeginPlay() override;

private:
    TFunction<double(double)> SymbolicTransformation;
    double ComputeRecursiveSymbol(int32 Depth) const;
};
