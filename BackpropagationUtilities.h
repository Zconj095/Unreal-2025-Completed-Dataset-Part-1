// Simple utility ported from Unity backpropagation helper.
#pragma once

#include "CoreMinimal.h"

namespace BackpropagationUtilities
{
    /** Returns a new array where each element is adjusted by the corresponding error. */
    inline TArray<float> AdjustVectors(const TArrayView<const float>& Vector, const TArrayView<const float>& Errors, float LearningRate)
    {
        const int32 Count = FMath::Min(Vector.Num(), Errors.Num());
        TArray<float> Result;
        Result.SetNumZeroed(Count);

        for (int32 Index = 0; Index < Count; ++Index)
        {
            Result[Index] = Vector[Index] - LearningRate * Errors[Index];
        }

        return Result;
    }
}
