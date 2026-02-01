#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SymbolicParserComponent.generated.h"

UENUM(BlueprintType)
enum class ESymbolicTransformType : uint8
{
    Identity UMETA(DisplayName="Identity"),
    Square UMETA(DisplayName="Square"),
    Sine UMETA(DisplayName="Sine"),
    Logarithm UMETA(DisplayName="Logarithm")
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API USymbolicParserComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USymbolicParserComponent();

    UFUNCTION(BlueprintCallable, Category="Symbolic Parser")
    double ProcessSymbols(const TArray<double>& Tokens);

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category="Symbolic Parser")
    TArray<double> Weights;

    UPROPERTY(EditAnywhere, Category="Symbolic Parser")
    TArray<ESymbolicTransformType> Transformations;

    static double ApplyTransformation(ESymbolicTransformType Type, double Value);
};
