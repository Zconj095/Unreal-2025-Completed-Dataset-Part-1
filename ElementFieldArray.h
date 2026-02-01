#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuantumElement.h"
#include "ElementFieldArray.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AElementFieldArray : public AActor
{
    GENERATED_BODY()

public:
    AElementFieldArray();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

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

    UPROPERTY(BlueprintReadOnly, Category="Element Field")
    TArray<FQuantumElement> FieldArray;

    UFUNCTION(BlueprintCallable, Category="Element Field")
    void InitializeField();

    UFUNCTION(BlueprintCallable, Category="Element Field")
    void SimulateFieldEvolution(float DeltaTime);

    UFUNCTION(BlueprintPure, Category="Element Field")
    float CalculateTotalFieldEnergy() const;

    UFUNCTION(BlueprintCallable, Category="Element Field|Debug")
    void VisualizeField();

    UFUNCTION(BlueprintPure, Category="Element Field")
    static int32 GetIndex(int32 I, int32 J, int32 InSizeX) { return I + J * InSizeX; }

private:
    int32 GetElementCount() const { return SizeX * SizeY; }
};

