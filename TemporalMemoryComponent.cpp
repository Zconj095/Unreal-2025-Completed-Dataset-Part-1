#include "TemporalMemoryComponent.h"

UTemporalMemoryComponent::UTemporalMemoryComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTemporalMemoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTemporalMemoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTemporalMemoryComponent::AddMemory(float Time, const TArray<float>& Memory, float Tau, float Prior)
{
    FTemporalMemory E; E.Time = Time; E.Memory = Memory; E.Tau = Tau; E.Prior = Prior;
    Memories.Add(E);
    Weights.SetNum(Memories.Num());
    OnMemoryAdded.Broadcast(E);
}

void UTemporalMemoryComponent::Retrieve(float StartTime, float EndTime, float TauMax, TArray<FTemporalMemory>& Out) const
{
    Out.Reset();
    for (const FTemporalMemory& E : Memories)
    {
        if (E.Time >= StartTime && E.Time <= EndTime && E.Tau <= TauMax)
        {
            Out.Add(E);
        }
    }
}

void UTemporalMemoryComponent::ApplyDelayDecay(float CurrentTime)
{
    for (FTemporalMemory& E : Memories)
    {
        const float dt = FMath::Max(0.0f, CurrentTime - E.Time);
        E.Tau = E.Tau * FMath::Exp(-Lambda * dt);
    }
}

float UTemporalMemoryComponent::PredictDelayAware(const FTemporalMemory& Entry) const
{
    const float z = Wt * Entry.Time + Wtau * Entry.Tau + B;
    return Sigmoid(z);
}

float UTemporalMemoryComponent::ComputeLossMSE(const TArray<float>& Targets, const TArray<float>& Predictions) const
{
    const int32 N = FMath::Min(Targets.Num(), Predictions.Num());
    if (N <= 0) { return 0.0f; }
    double Sum = 0.0;
    for (int32 i = 0; i < N; ++i)
    {
        const double d = (double)Targets[i] - (double)Predictions[i];
        Sum += d * d;
    }
    // Delay penalty term
    double Pen = 0.0;
    for (const FTemporalMemory& E : Memories) { Pen += (double)E.Tau * (double)E.Tau; }
    return (float)(Sum / (double)N + Gamma * Pen);
}

void UTemporalMemoryComponent::OnlineUpdateParams(const TArray<FTemporalMemory>& Batch, const TArray<float>& Targets, float LearnRate)
{
    const int32 N = FMath::Min(Batch.Num(), Targets.Num());
    if (N <= 0) { return; }
    double dWt = 0.0, dWtau = 0.0, dB = 0.0;
    for (int32 i = 0; i < N; ++i)
    {
        const float y = Targets[i];
        const float yhat = PredictDelayAware(Batch[i]);
        const float err = (yhat - y); // d/dz for sigmoid+MSE -> (yhat - y)
        dWt   += err * Batch[i].Time;
        dWtau += err * Batch[i].Tau + 2.0 * Gamma * Batch[i].Tau; // includes delay penalty grad
        dB    += err;
    }
    const double scale = (double)LearnRate / (double)N;
    Wt   -= (float)(scale * dWt);
    Wtau -= (float)(scale * dWtau);
    B    -= (float)(scale * dB);
}

float UTemporalMemoryComponent::ComputeRt(float t, float Mt, float Tau) const
{
    return Mt * FMath::Exp(-Alpha * t + Beta * Tau);
}

float UTemporalMemoryComponent::ComputeQt(float Rt, float DeltaT, float Tau) const
{
    return Rt / FMath::Max(1e-4f, (DeltaT + Tau));
}

static float L2Norm(const TArray<float>& V)
{
    double s = 0.0; for (float x : V) { s += (double)x * (double)x; } return (float)FMath::Sqrt(s);
}

float UTemporalMemoryComponent::DotCosine(const TArray<float>& A, const TArray<float>& B)
{
    const int32 N = FMath::Min(A.Num(), B.Num());
    if (N <= 0) { return 0.0f; }
    double dot = 0.0; for (int32 i = 0; i < N; ++i) { dot += (double)A[i] * (double)B[i]; }
    const float na = L2Norm(A), nb = L2Norm(B);
    if (na <= 1e-6f || nb <= 1e-6f) { return 0.0f; }
    return (float)(dot / ((double)na * (double)nb));
}

float UTemporalMemoryComponent::ComputeRa(const TArray<float>& Query) const
{
    double Ra = 0.0;
    for (int32 i = 0; i < Memories.Num(); ++i)
    {
        const FTemporalMemory& E = Memories[i];
        const float cos = DotCosine(E.Memory, Query);
        const double term = (double)cos * (double)E.Prior * FMath::Exp(-Kappa * E.Tau);
        Ra += term;
    }
    return (float)Ra;
}

void UTemporalMemoryComponent::ComputeRecallAndRe(float t, float Context, float& OutR, float& OutRe) const
{
    // Aggregate R using current memories (Mt = ||m||)
    double Rsum = 0.0, SumTau = 0.0;
    for (const FTemporalMemory& E : Memories)
    {
        const float Mt = L2Norm(E.Memory);
        Rsum += ComputeRt(t - E.Time, Mt, E.Tau);
        SumTau += E.Tau;
    }
    OutR = (float)Rsum;
    OutRe = RScalar * Context * FMath::Exp(-(float)SumTau / FMath::Max(1e-4f, GlobalTimeConstantT));
}

float UTemporalMemoryComponent::StepPLL(float TargetTime, float ActualTime, float Omega, float DeltaTime)
{
    const float error = TargetTime - ActualTime; // (t_target - t_actual)
    Phase = Phase + Omega * DeltaTime + Mu * error;
    OnPLLUpdated.Broadcast(Phase);
    return Phase;
}

void UTemporalMemoryComponent::ApplySTDP(float Eta, float TauSTDP)
{
    if (Memories.Num() <= 1) { return; }
    Weights.SetNum(Memories.Num());
    for (int32 i = 0; i < Memories.Num(); ++i)
    {
        double dw = 0.0;
        for (int32 j = 0; j < Memories.Num(); ++j)
        {
            if (i == j) { continue; }
            const float dt = FMath::Abs(Memories[i].Time - Memories[j].Time);
            dw += Eta * FMath::Exp(-dt / FMath::Max(1e-4f, TauSTDP));
        }
        Weights[i] += (float)dw;
    }
}

float UTemporalMemoryComponent::ComputeAdaptiveThreshold() const
{
    double sum = 0.0;
    const int32 N = FMath::Min(Weights.Num(), Memories.Num());
    for (int32 i = 0; i < N; ++i)
    {
        sum += (double)Weights[i] * (double)Memories[i].Tau;
    }
    return Theta0 + (float)sum;
}

