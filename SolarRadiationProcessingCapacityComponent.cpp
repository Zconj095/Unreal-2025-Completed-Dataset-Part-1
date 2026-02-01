#include "SolarRadiationProcessingCapacityComponent.h"

#include "Math/UnrealMathUtility.h"

USolarRadiationProcessingCapacityComponent::USolarRadiationProcessingCapacityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USolarRadiationProcessingCapacityComponent::BeginPlay()
{
    Super::BeginPlay();
}

void USolarRadiationProcessingCapacityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    const float SolarMemoryCapacity = CalculateSRPC(EncodingEfficiency, MinWavelength, MaxWavelength, Steps);
    UE_LOG(LogTemp, Log, TEXT("Solar Memory Capacity (Ms): %.2f"), SolarMemoryCapacity);
}

float USolarRadiationProcessingCapacityComponent::CalculateSRPC(float Alpha, float LambdaMin, float LambdaMax, int32 StepCount) const
{
    if (StepCount <= 0 || LambdaMax <= LambdaMin)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid wavelength range or steps."));
        return 0.0f;
    }

    const float DeltaLambda = (LambdaMax - LambdaMin) / StepCount;
    float IntegralSum = 0.0f;

    for (int32 Index = 0; Index <= StepCount; ++Index)
    {
        const float Lambda = LambdaMin + Index * DeltaLambda;
        IntegralSum += SolarRadiationIntensity(Lambda) * DeltaLambda;
    }

    return Alpha * IntegralSum;
}

float USolarRadiationProcessingCapacityComponent::SolarRadiationIntensity(float Lambda) const
{
    constexpr float CenterWavelength = 550.0f;
    constexpr float Width = 100.0f;
    return FMath::Exp(-FMath::Square(Lambda - CenterWavelength) / (2.0f * Width * Width));
}
