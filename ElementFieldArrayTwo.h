#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElementalTypeTwo.h"
#include "QuantumElementTwo.h"
#include "ElementFieldArrayTwo.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AElementFieldArrayTwo : public AActor
{
    GENERATED_BODY()

public:
    AElementFieldArrayTwo();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // Dimensions of the element field
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    int32 SizeX = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    int32 SizeY = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    bool bAutoInitializeOnBeginPlay = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    bool bAutoSimulate = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    bool bAutoVisualize = false;

    // Storage as 1D array: index = i + j*SizeX
    UPROPERTY(BlueprintReadOnly, Category="Element Field")
    TArray<FQuantumElementTwo> FieldArray;

    UFUNCTION(BlueprintCallable, Category="Element Field")
    void InitializeField();

    UFUNCTION(BlueprintCallable, Category="Element Field")
    void SimulateFieldEvolution(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category="Element Field")
    void SimulateElementalInteractions();

    UFUNCTION(BlueprintCallable, Category="Element Field|Debug")
    void VisualizeField();

    UFUNCTION(BlueprintPure, Category="Element Field")
    static int32 GetIndex(int32 I, int32 J, int32 InSizeX) { return I + J * InSizeX; }

    UFUNCTION(BlueprintPure, Category="Element Field|Debug")
    static FColor ElementalTypeToColor(EElementalTypeTwo Type);

private:
    int32 GetElementCount() const { return SizeX * SizeY; }
};

