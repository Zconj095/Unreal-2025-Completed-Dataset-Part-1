// Interleaved position buffer utilities and GPU-style transform math
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ChunkBufferAndTransformLibrary.generated.h"

USTRUCT(BlueprintType)
struct PEKBGGAP_API FInterleavedPositionBuffer
{
    GENERATED_BODY()

    // Buffer layout: [x1, y1, z1, x2, y2, z2, ...]
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buffer")
    TArray<float> Buffer;

    void Init(int32 NumChunks)
    {
        Buffer.SetNum(NumChunks * 3);
    }

    void SetChunkPosition(int32 Index, const FVector& P)
    {
        const int32 Base = Index * 3;
        if (Buffer.Num() >= Base + 3)
        {
            Buffer[Base + 0] = P.X;
            Buffer[Base + 1] = P.Y;
            Buffer[Base + 2] = P.Z;
        }
    }

    FVector GetChunkPosition(int32 Index) const
    {
        const int32 Base = Index * 3;
        if (Buffer.Num() >= Base + 3)
        {
            return FVector(Buffer[Base + 0], Buffer[Base + 1], Buffer[Base + 2]);
        }
        return FVector::ZeroVector;
    }
};

UCLASS()
class PEKBGGAP_API UChunkBufferAndTransformLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Fill interleaved buffer from transforms (uses world positions only)
    UFUNCTION(BlueprintCallable, Category="Buffer")
    static void InterleavePositionsFromTransforms(const TArray<FTransform>& Transforms, FInterleavedPositionBuffer& OutBuffer)
    {
        OutBuffer.Init(Transforms.Num());
        for (int32 i = 0; i < Transforms.Num(); ++i)
        {
            OutBuffer.SetChunkPosition(i, Transforms[i].GetLocation());
        }
    }

    // Build transform matrix T combining scale (sx,sy,sz), rotation (Rot), translation (tx,ty,tz)
    UFUNCTION(BlueprintPure, Category="Transform")
    static FMatrix BuildTransformMatrix(const FVector& Scale, const FRotator& Rot, const FVector& Translation)
    {
        const FTransform Tr(Rot, Translation, Scale);
        return Tr.ToMatrixWithScale();
    }

    // Compute P' = T * P (homogeneous), P = [x y z 1]
    UFUNCTION(BlueprintPure, Category="Transform")
    static FVector TransformPosition(const FMatrix& Transform, const FVector& P)
    {
        const FVector4 HP(P, 1.0f);
        const FVector4 Transformed = Transform.TransformFVector4(HP);
        return FVector(Transformed.X, Transformed.Y, Transformed.Z);
    }
};
