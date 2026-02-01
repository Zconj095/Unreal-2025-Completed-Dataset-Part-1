// Temporal Memory with Advanced Timing Relay and Delay-Based Pattern Recognition (Blueprint-ready)
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TemporalMemoryComponent.generated.h"

USTRUCT(BlueprintType)
struct PEKBGGAP_API FTemporalMemory
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM")
    float Time = 0.0f; // t_i

    // Memory payload vector m_i (arbitrary dimension)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM")
    TArray<float> Memory;

    // Adaptive delay tau_i
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM")
    float Tau = 0.0f;

    // Optional prior weight P(x_i)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM")
    float Prior = 1.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTMOnMemoryAdded, const FTemporalMemory&, Entry);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTMOnRecallComputed, float, R, float, Re);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTMOnPLLUpdated, float, Phase);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UTemporalMemoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTemporalMemoryComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // --- Storage ---
    UFUNCTION(BlueprintCallable, Category="TM|Storage")
    void AddMemory(float Time, const TArray<float>& Memory, float Tau, float Prior = 1.0f);

    UFUNCTION(BlueprintCallable, Category="TM|Storage")
    void Retrieve(float StartTime, float EndTime, float TauMax, TArray<FTemporalMemory>& Out) const;

    UFUNCTION(BlueprintCallable, Category="TM|Storage")
    void ApplyDelayDecay(float CurrentTime);

    // --- Prediction ---
    UFUNCTION(BlueprintCallable, Category="TM|Prediction")
    float PredictDelayAware(const FTemporalMemory& Entry) const; // sigma(W·[t, tau] + b)

    UFUNCTION(BlueprintCallable, Category="TM|Prediction")
    float ComputeLossMSE(const TArray<float>& Targets, const TArray<float>& Predictions) const;

    UFUNCTION(BlueprintCallable, Category="TM|Prediction")
    void OnlineUpdateParams(const TArray<FTemporalMemory>& Batch, const TArray<float>& Targets, float LearnRate);

    // --- Recall ---
    UFUNCTION(BlueprintCallable, Category="TM|Recall")
    float ComputeRt(float t, float Mt, float Tau) const; // R_t

    UFUNCTION(BlueprintCallable, Category="TM|Recall")
    float ComputeQt(float Rt, float DeltaT, float Tau) const; // Q_t

    UFUNCTION(BlueprintCallable, Category="TM|Recall")
    float ComputeRa(const TArray<float>& Query) const; // associative

    UFUNCTION(BlueprintCallable, Category="TM|Recall")
    void ComputeRecallAndRe(float t, float Context, float& OutR, float& OutRe) const;

    // --- Timing Relay ---
    UFUNCTION(BlueprintCallable, Category="TM|PLL")
    float StepPLL(float TargetTime, float ActualTime, float Omega, float DeltaTime);

    UFUNCTION(BlueprintCallable, Category="TM|STDP")
    void ApplySTDP(float Eta, float TauSTDP);

    UFUNCTION(BlueprintCallable, Category="TM|Threshold")
    float ComputeAdaptiveThreshold() const; // theta_t

    // --- Config ---
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Params")
    float Lambda = 0.1f; // delay decay

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Params")
    float Gamma = 0.001f; // delay penalty in loss

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Params")
    float Alpha = 0.2f; // R_t decay

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Params")
    float Beta = 0.4f; // R_t delay sensitivity

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Params")
    float Kappa = 0.2f; // associative delay scaling

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Params")
    float GlobalTimeConstantT = 10.0f; // T for Re

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Params")
    float RScalar = 1.0f; // r multiplier in Re

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Params")
    float Theta0 = 0.1f; // base threshold

    // PLL params (phase = phi)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|PLL")
    float Mu = 1.0f; // synchronization rate

    UPROPERTY(BlueprintReadOnly, Category="TM|PLL")
    float Phase = 0.0f; // phi

    // Linear predictor parameters: y_hat = sigma(W_t * t + W_tau * tau + b)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Prediction")
    float Wt = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Prediction")
    float Wtau = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TM|Prediction")
    float B = 0.0f;

    // Storage
    UPROPERTY(BlueprintReadOnly, Category="TM|Storage")
    TArray<FTemporalMemory> Memories;

    // STDP running weights per memory index (for adaptive thresholding)
    UPROPERTY(BlueprintReadOnly, Category="TM|STDP")
    TArray<float> Weights;

    // Events
    UPROPERTY(BlueprintAssignable, Category="TM|Events")
    FTMOnMemoryAdded OnMemoryAdded;

    UPROPERTY(BlueprintAssignable, Category="TM|Events")
    FTMOnRecallComputed OnRecallComputed;

    UPROPERTY(BlueprintAssignable, Category="TM|Events")
    FTMOnPLLUpdated OnPLLUpdated;

private:
    static float Sigmoid(float x) { return 1.0f / (1.0f + FMath::Exp(-x)); }
    static float DotCosine(const TArray<float>& A, const TArray<float>& B);
};

