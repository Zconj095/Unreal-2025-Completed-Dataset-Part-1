#include "TemporalMemoryDemoActor.h"
#include "Engine/World.h"

ATemporalMemoryDemoActor::ATemporalMemoryDemoActor()
{
    PrimaryActorTick.bCanEverTick = true;
    TM = CreateDefaultSubobject<UTemporalMemoryComponent>(TEXT("TemporalMemory"));
}

void ATemporalMemoryDemoActor::BeginPlay()
{
    Super::BeginPlay();
}

void ATemporalMemoryDemoActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const float t = GetWorld()->TimeSeconds;

    // Periodically add memories
    TimeSinceAdd += DeltaSeconds;
    if (TimeSinceAdd >= AddInterval)
    {
        TimeSinceAdd = 0.0f;
        TArray<float> m; m.SetNum(Dim);
        for (int32 i = 0; i < Dim; ++i) { m[i] = FMath::FRandRange(-1.0f, 1.0f); }
        const float tau = FMath::FRandRange(0.05f, 0.5f);
        TM->AddMemory(t, m, tau, 1.0f);
        TM->ApplyDelayDecay(t);
    }

    // Periodically query recall
    TimeSinceQuery += DeltaSeconds;
    if (TimeSinceQuery >= QueryInterval)
    {
        TimeSinceQuery = 0.0f;
        float R=0, Re=0; TM->ComputeRecallAndRe(t, /*Context*/1.0f, R, Re);
        const float theta = TM->ComputeAdaptiveThreshold();
        UE_LOG(LogTemp, Log, TEXT("[TM] t=%.2f R=%.3f Re=%.3f theta=%.3f memories=%d"), t, R, Re, theta, TM->Memories.Num());
    }
}

