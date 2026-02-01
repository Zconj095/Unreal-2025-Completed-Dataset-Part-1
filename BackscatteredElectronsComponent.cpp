// Converted from Unity MonoBehaviour to Unreal ActorComponent.
#include "BackscatteredElectronsComponent.h"

#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "MaterialPropertiesComponent.h"
#include "Math/UnrealMathUtility.h"

UBackscatteredElectronsComponent::UBackscatteredElectronsComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UBackscatteredElectronsComponent::BeginPlay()
{
    Super::BeginPlay();

    CreateBseTexture();
    SimulateBackscatteredElectrons();
}

void UBackscatteredElectronsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (bAutoSimulate)
    {
        SimulateBackscatteredElectrons();
    }
}

void UBackscatteredElectronsComponent::CreateBseTexture()
{
    Resolution = FMath::Max(1, Resolution);
    PixelBuffer.SetNumZeroed(Resolution * Resolution);

    BseTexture = UTexture2D::CreateTransient(Resolution, Resolution, PF_B8G8R8A8);
    if (BseTexture)
    {
        BseTexture->CompressionSettings = TextureCompressionSettings::TC_Default;
        BseTexture->SRGB = false;
        BseTexture->AddToRoot();
        BseTexture->UpdateResource();
    }
}

void UBackscatteredElectronsComponent::SimulateBackscatteredElectrons()
{
    if (!GetWorld() || Resolution <= 0)
    {
        return;
    }

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        return;
    }

    PixelBuffer.SetNumZeroed(Resolution * Resolution);

    const FVector Forward = Owner->GetActorForwardVector();
    const FVector Right = Owner->GetActorRightVector();
    const FVector Up = Owner->GetActorUpVector();
    const FVector CameraOrigin = Owner->GetActorLocation() - Forward * 10.0f;
    const float PixelWidth = CaptureSize.X / Resolution;
    const float PixelHeight = CaptureSize.Y / Resolution;
    const float HalfWidth = CaptureSize.X * 0.5f;
    const float HalfHeight = CaptureSize.Y * 0.5f;
    const int32 TotalPixels = Resolution * Resolution;

    FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(BackscatterTrace), false, GetOwner());
    QueryParams.bReturnPhysicalMaterial = false;

    for (int32 Y = 0; Y < Resolution; ++Y)
    {
        const float YOffset = (Y + 0.5f) * PixelHeight - HalfHeight;
        for (int32 X = 0; X < Resolution; ++X)
        {
            const float XOffset = (X + 0.5f) * PixelWidth - HalfWidth;
            const FVector RayStart = CameraOrigin + Right * XOffset + Up * YOffset;
            const FVector RayEnd = RayStart + Forward * TraceDistance;

            float IntensityValue = 0.0f;
            FHitResult Hit;
            if (GetWorld()->LineTraceSingleByChannel(Hit, RayStart, RayEnd, TraceChannel, QueryParams))
            {
                const float Dot = FMath::Clamp(FVector::DotProduct(Forward, Hit.ImpactNormal.GetSafeNormal()), -1.0f, 1.0f);
                const float DetectionAngle = FMath::RadiansToDegrees(FMath::Acos(Dot));

                float AtomicNumber = 1.0f;
                if (const AActor* HitActor = Hit.GetActor())
                {
                    if (const UMaterialPropertiesComponent* MaterialProps = HitActor->FindComponentByClass<UMaterialPropertiesComponent>())
                    {
                        AtomicNumber = MaterialProps->AtomicNumber;
                    }
                }

                if (DetectionAngle <= MaxDetectionAngle)
                {
                    IntensityValue = AtomicNumber * IntensityMultiplier;
                }
            }

            const float ClampedIntensity = FMath::Clamp(IntensityValue, 0.0f, 1.0f);
            const uint8 ByteValue = FMath::RoundToInt(ClampedIntensity * 255.0f);
            const int32 PixelIndex = FMath::Clamp(X + Y * Resolution, 0, TotalPixels - 1);
            PixelBuffer[PixelIndex] = FColor(ByteValue, ByteValue, ByteValue, 255);
        }
    }

    UpdateTexture();
}

void UBackscatteredElectronsComponent::UpdateTexture()
{
    if (!BseTexture || PixelBuffer.Num() == 0)
    {
        return;
    }

    FTexturePlatformData* PlatformData = BseTexture->GetPlatformData();
    if (!PlatformData || PlatformData->Mips.Num() == 0)
    {
        return;
    }

    FTexture2DMipMap& Mip = PlatformData->Mips[0];
    void* TextureData = Mip.BulkData.Lock(LOCK_READ_WRITE);
    FMemory::Memcpy(TextureData, PixelBuffer.GetData(), PixelBuffer.Num() * sizeof(FColor));
    Mip.BulkData.Unlock();
    BseTexture->UpdateResource();
}

void UBackscatteredElectronsComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
    if (BseTexture)
    {
        BseTexture->RemoveFromRoot();
        BseTexture = nullptr;
    }

    Super::OnComponentDestroyed(bDestroyingHierarchy);
}
