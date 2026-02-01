#include "RunicCoreSector2Component.h"

#include <cmath>

URunicCoreSector2Component::URunicCoreSector2Component()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void URunicCoreSector2Component::BeginPlay()
{
    Super::BeginPlay();

    SymbolicTransformation = [](double Input)
    {
        return tgamma(Input + 1.0);
    };

    const int32 Depth = 5;
    const double Result = ComputeRecursiveSymbol(Depth);

    UE_LOG(LogTemp, Log, TEXT("R(%d) = %.6f"), Depth, Result);
}

double URunicCoreSector2Component::ComputeRecursiveSymbol(int32 Depth) const
{
    if (Depth <= 0)
    {
        return 1.0;
    }

    return SymbolicTransformation(ComputeRecursiveSymbol(Depth - 1));
}
