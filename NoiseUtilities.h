// Utility converted from Unity C# helper to Unreal Engine C++.
#pragma once

#include "CoreMinimal.h"
#include "Async/ParallelFor.h"

namespace NoiseUtilities
{
    /** Adds uniform noise in-place to each element of the array. */
    inline void AddNoiseInPlace(TArray<float>& Values, float NoiseLevel)
    {
        for (float& Value : Values)
        {
            Value += FMath::FRandRange(-NoiseLevel, NoiseLevel);
        }
    }

    /**
     * Parallel job equivalent of the Unity burst job, writing noisy values out-of-place.
     * A simple deterministic seed is combined with the index to keep each range call unique.
     */
    inline void AddNoiseJobToBoot(const TArray<float>& OriginalValues, TArray<float>& NoisyValues, float NoiseLevel, int32 BootSeed = 13579)
    {
        const int32 Count = FMath::Min(OriginalValues.Num(), NoisyValues.Num());
        ParallelFor(Count, [&](int32 Index)
        {
            FRandomStream RandStream(BootSeed + Index);
            const float Noise = RandStream.FRandRange(-NoiseLevel, NoiseLevel);
            NoisyValues[Index] = OriginalValues[Index] + Noise;
        });
    }
}
