#include "SylvanicGlandComponent.h"
#include "Engine/World.h"

#include "Math/UnrealMathUtility.h"

USylvanicGlandComponent::USylvanicGlandComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USylvanicGlandComponent::BeginPlay()
{
    Super::BeginPlay();
    ElapsedTime = 0.0f;
    ManaPotency = CalculateManaPotency(0.0f);
    UE_LOG(LogTemp, Log, TEXT("Sylvanic Gland initialized. Initial Mana Potency (Pm): %.2f"), ManaPotency);
}

void USylvanicGlandComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    SimulateManaOutput(DeltaTime);
    ManaPotency = CalculateManaPotency(GetWorld()->GetTimeSeconds());
}

void USylvanicGlandComponent::SimulateManaOutput(float DeltaTime)
{
    if (ElapsedTime > SimulationTime)
    {
        return;
    }

    ElapsedTime += DeltaTime;
    if (ElapsedTime > SimulationTime)
    {
        ElapsedTime = SimulationTime;
    }

    ManaPotency = CalculateManaPotency(ElapsedTime);
    UE_LOG(LogTemp, Log, TEXT("Time: %.2fs, Mana Potency (Pm): %.2f"), ElapsedTime, ManaPotency);
}

float USylvanicGlandComponent::CalculateManaPotency(float Time) const
{
    return ReleaseRate * FMath::Exp(-ManaDecayRate * Time);
}
