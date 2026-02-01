// Noise-driven texture blending helpers (CPU/Blueprint-side). For materials, map outputs into parameters.
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextureBlendingLibrary.generated.h"

UCLASS()
class PEKBGGAP_API UTextureBlendingLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Compute 4-layer weights T(x,y,z) = sum_k Wk * Tk (weights only; Tk are textures in material). Height/slope drive weights; noise perturbs boundaries.
    UFUNCTION(BlueprintPure, Category="Blending")
    static FLinearColor ComputeBlendWeights4(float Height, float Slope, float NoiseScale, int32 Seed,
                                             const FVector4& LayerHeights, float Sharpness = 8.0f)
    {
        // Base logits from height thresholds
        float logits[4];
        const float h = Height;
        logits[0] = -(h - LayerHeights.X);
        logits[1] = -(h - LayerHeights.Y);
        logits[2] = -(h - LayerHeights.Z);
        logits[3] = -(h - LayerHeights.W);

        // Slope pushes weight toward rockier layers (higher indices)
        const float slopeBias = FMath::Clamp(Slope, 0.0f, 1.0f);
        logits[2] += slopeBias * 0.5f;
        logits[3] += slopeBias * 1.0f;

        // Low-frequency noise to avoid banding
        const float nx = FMath::PerlinNoise1D((Height + Seed * 0.0131f) * (NoiseScale <= 0 ? 1.0f : NoiseScale));
        logits[0] += nx * 0.05f; logits[1] += nx * 0.03f; logits[2] -= nx * 0.02f; logits[3] -= nx * 0.04f;

        // Softmax with adjustable sharpness
        const float s = FMath::Max(0.001f, Sharpness);
        float exps[4];
        float sum = 0.0f;
        for (int i = 0; i < 4; ++i) { exps[i] = FMath::Exp(logits[i] * s); sum += exps[i]; }
        if (sum <= KINDA_SMALL_NUMBER) { return FLinearColor(1,0,0,0); }
        const float w0 = exps[0] / sum;
        const float w1 = exps[1] / sum;
        const float w2 = exps[2] / sum;
        const float w3 = exps[3] / sum;
        return FLinearColor(w0, w1, w2, w3); // RGBA as 4 weights
    }
};

