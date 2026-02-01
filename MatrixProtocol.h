#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixProtocol.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixProtocol : public AActor
{
    GENERATED_BODY()

public:
    AMatrixProtocol();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Protocol")
    int64 ProcessPath(const FString& Path);

    UFUNCTION(BlueprintCallable, Category = "Matrix Protocol")
    double GenerateFormulaicResponse(int64 ComputedResult) const;

    UFUNCTION(BlueprintCallable, Category = "Matrix Protocol")
    void HandleUnknownData(const FString& UnknownData);

protected:
    UPROPERTY(EditAnywhere, Category = "Automation")
    float ProcessPathInterval = 5.f; // seconds

    UPROPERTY(EditAnywhere, Category = "Automation")
    float HandleUnknownDataInterval = 10.f; // seconds

private:
    // Using array lookup [0..9] rather than a map for performance and simplicity
    static const int64 ProtocolFormula[10];

    // Timers
    float ProcessPathTimer = 0.f;
    float HandleUnknownDataTimer = 0.f;
};

