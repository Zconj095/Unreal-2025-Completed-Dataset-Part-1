#include "FluxSignalActor.h"

AFluxSignalActor::AFluxSignalActor()
{
    PrimaryActorTick.bCanEverTick = true;
    FluxComponent = CreateDefaultSubobject<UFluxSignalGeneratorComponent>(TEXT("FluxComponent"));
}

void AFluxSignalActor::BeginPlay()
{
    Super::BeginPlay();

    if (FluxComponent)
    {
        FluxComponent->OnFluxSample.AddDynamic(this, &AFluxSignalActor::OnFluxSample);
    }
}

void AFluxSignalActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AFluxSignalActor::OnFluxSample(float Value, const TArray<float>& Channels)
{
    if (!bLogSamples) { return; }

    if (Channels.Num() <= 1)
    {
        UE_LOG(LogTemp, Log, TEXT("Monoflux Sample: %0.3f"), Value);
    }
    else
    {
        FString ChanStr;
        for (int32 i = 0; i < Channels.Num(); ++i)
        {
            ChanStr += FString::Printf(TEXT("%s%0.3f"), (i==0?TEXT(""):TEXT(", ")), Channels[i]);
        }
        UE_LOG(LogTemp, Log, TEXT("Hyperflux Sum: %0.3f | Channels: [%s]"), Value, *ChanStr);
    }
}
