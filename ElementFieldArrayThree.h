#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuantumElementThree.h"
#include "ElementFieldArrayThree.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AElementFieldArrayThree : public AActor
{
    GENERATED_BODY()

public:
    AElementFieldArrayThree();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    int32 SizeX = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    int32 SizeY = 8;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    bool bAutoInitializeOnBeginPlay = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    bool bAutoBuildNetwork = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    bool bAutoSimulate = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Element Field")
    bool bAutoVisualize = false;

    UPROPERTY(BlueprintReadOnly, Category="Element Field")
    TArray<FQuantumElementThree> FieldArray;

    UFUNCTION(BlueprintCallable, Category="Element Field")
    void InitializeField();

    UFUNCTION(BlueprintCallable, Category="Element Field")
    void BuildPossibilityNetwork();

    UFUNCTION(BlueprintCallable, Category="Element Field")
    void SimulateFieldEvolution(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category="Element Field|Debug")
    void VisualizeField();

    UFUNCTION(BlueprintPure, Category="Element Field")
    static int32 GetIndex(int32 I, int32 J, int32 InSizeX) { return I + J * InSizeX; }

    UFUNCTION(BlueprintPure, Category="Element Field|Debug")
    static FColor ElementalTypeToColor(EElementalTypeTwo Type);

private:
    int32 GetElementCount() const { return SizeX * SizeY; }
    void AddConnectionBetweenElements(int32 AIdx, int32 BIdx);
};

