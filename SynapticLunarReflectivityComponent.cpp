#include "SynapticLunarReflectivityComponent.h"

#include "Math/UnrealMathUtility.h"

USynapticLunarReflectivityComponent::USynapticLunarReflectivityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USynapticLunarReflectivityComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentTime = 0.0f;
}

void USynapticLunarReflectivityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    CurrentTime += DeltaTime;
    LunarReflectivity = CalculateLunarReflectivity(CurrentTime);

    UE_LOG(LogTemp, Log, TEXT("Synaptic Lunar Reflectivity: %.4f"), LunarReflectivity);
}

float USynapticLunarReflectivityComponent::CalculateLunarReflectivity(float Time) const
{
    return BaseReflectivity * (1.0f + LunarSensitivity * FMath::Sin(AngularFrequency * Time + PhaseOffset));
}
