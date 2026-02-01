#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AtomicLatticeComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PEKBGGAP_API UAtomicLatticeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UAtomicLatticeComponent();

protected:
	virtual void BeginPlay() override;

public:
	/** First basis vector. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Lattice")
	FVector BasisVector1 = FVector::ForwardVector;

	/** Second basis vector. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Lattice")
	FVector BasisVector2 = FVector::RightVector;

	/** Third basis vector. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Lattice")
	FVector BasisVector3 = FVector::UpVector;

	/** Range used by default to build a lattice at BeginPlay. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Atomic Lattice", meta = (ClampMin = "0"))
	int32 DefaultRange = 2;

	/** Cached lattice points generated at BeginPlay. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Atomic Lattice")
	TArray<FVector> GeneratedLatticePoints;

	/** Calculates position for a lattice point given (n1, n2, n3). */
	UFUNCTION(BlueprintCallable, Category = "Atomic Lattice")
	FVector CalculateLatticePoint(int32 N1, int32 N2, int32 N3) const;

	/** Generates all lattice points within the provided range (inclusive). */
	UFUNCTION(BlueprintCallable, Category = "Atomic Lattice")
	TArray<FVector> GenerateLatticePoints(int32 Range) const;
};
