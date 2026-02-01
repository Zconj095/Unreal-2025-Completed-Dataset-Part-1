// SIMD helper adapted from the Unity C# noise generator.
#pragma once

#include "CoreMinimal.h"
#include "Math/UnrealMathUtility.h"
#include "Math/VectorRegister.h"

namespace NoiseUtilities
{
    /**
     * Processes a chunk of floats using vector registers, similar to Vector<T> in .NET.
     * Random noise is generated per element with a seeded stream to remain deterministic.
     */
    inline void AddNoiseSIMD(const TArrayView<const float>& Input, const TArrayView<float>& Output, float NoiseLevel, int32 Seed = 24601)
    {
        const int32 Count = FMath::Min(Input.Num(), Output.Num());
        if (Count == 0)
        {
            return;
        }

        FRandomStream Random(Seed);
        constexpr int32 SIMDWidth = VectorRegister::FloatVectorWidth;
        int32 Index = 0;

        // Process full SIMD chunks.
        for (; Index + SIMDWidth <= Count; Index += SIMDWidth)
        {
            VectorRegister Data = VectorLoad(&Input[Index]);
            float NoiseValues[SIMDWidth];
            for (int32 Offset = 0; Offset < SIMDWidth; ++Offset)
            {
                NoiseValues[Offset] = Random.FRandRange(-NoiseLevel, NoiseLevel);
            }

            VectorRegister Noise = VectorLoad(NoiseValues);
            VectorRegister Result = VectorAdd(Data, Noise);
            VectorStore(Result, &Output[Index]);
        }

        // Tail elements that don't fit into a SIMD width.
        for (; Index < Count; ++Index)
        {
            Output[Index] = Input[Index] + Random.FRandRange(-NoiseLevel, NoiseLevel);
        }
    }
}
