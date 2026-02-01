#include "AttentionListeningAndHearingManager.h"
#include "Math/UnrealMathUtility.h"

namespace
{
    FORCEINLINE int W1Index(int r, int c, int Hidden, int Input) { return r * Input + c; }
    FORCEINLINE int W2Index(int r, int c, int Output, int Hidden) { return r * Hidden + c; }
}

double UAttentionListeningAndHearingManager::Sigmoid(double x)
{
    // Clamp to avoid overflow
    x = FMath::Clamp(x, -50.0, 50.0);
    return 1.0 / (1.0 + FMath::Exp(-x));
}

double UAttentionListeningAndHearingManager::SigmoidDerivFromActivation(double a)
{
    // derivative using activation value: a * (1 - a)
    return a * (1.0 - a);
}

void UAttentionListeningAndHearingManager::RandomizeParams(double Scale)
{
    W1.SetNumZeroed(HiddenSize * InputSize);
    b1.SetNumZeroed(HiddenSize);
    W2.SetNumZeroed(OutputSize * HiddenSize);
    b2.SetNumZeroed(OutputSize);

    for (int i = 0; i < W1.Num(); ++i)
    {
        W1[i] = FMath::FRandRange(-Scale, Scale);
    }
    for (int i = 0; i < b1.Num(); ++i)
    {
        b1[i] = 0.0;
    }
    for (int i = 0; i < W2.Num(); ++i)
    {
        W2[i] = FMath::FRandRange(-Scale, Scale);
    }
    for (int i = 0; i < b2.Num(); ++i)
    {
        b2[i] = 0.0;
    }
}

void UAttentionListeningAndHearingManager::InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize)
{
    InputSize = InInputSize;
    HiddenSize = InHiddenNeurons;
    OutputSize = InOutputSize;

    RandomizeParams(0.1);
}

void UAttentionListeningAndHearingManager::AddAuditoryData(double Ia, double Na, double Ht)
{
    const double Al = CalculateAuditoryAttention(Ia, Na);
    const double H = CalculateHearing(Ia, Na, Ht);
    AuditoryDataEntries.Add(FAuditoryData(Ia, Na, Ht, Al, H));
}

double UAttentionListeningAndHearingManager::CalculateAuditoryAttention(double Ia, double Na) const
{
    // ia * (1 - (na / (ia + na)))
    const double denom = Ia + Na;
    if (denom == 0.0) return 0.0;
    return Ia * (1.0 - (Na / denom));
}

double UAttentionListeningAndHearingManager::CalculateHearing(double Ia, double Na, double Ht) const
{
    // Step function: ia * (Ht - Na > 0 ? 1 : 0)
    return Ia * ((Ht - Na > 0.0) ? 1.0 : 0.0);
}

void UAttentionListeningAndHearingManager::ForwardSingle(const double* InX, TArray<double>& Z1, TArray<double>& A1, TArray<double>& Z2, TArray<double>& A2) const
{
    Z1.SetNumUninitialized(HiddenSize);
    A1.SetNumUninitialized(HiddenSize);
    for (int h = 0; h < HiddenSize; ++h)
    {
        double z = b1[h];
        for (int i = 0; i < InputSize; ++i)
        {
            z += W1[W1Index(h, i, HiddenSize, InputSize)] * InX[i];
        }
        Z1[h] = z;
        A1[h] = Sigmoid(z);
    }

    Z2.SetNumUninitialized(OutputSize);
    A2.SetNumUninitialized(OutputSize);
    for (int o = 0; o < OutputSize; ++o)
    {
        double z = b2[o];
        for (int h = 0; h < HiddenSize; ++h)
        {
            z += W2[W2Index(o, h, OutputSize, HiddenSize)] * A1[h];
        }
        Z2[o] = z;
        A2[o] = Sigmoid(z);
    }
}

double UAttentionListeningAndHearingManager::TrainNetwork(int32 Epochs, double LearningRate)
{
    if (AuditoryDataEntries.Num() == 0 || InputSize == 0 || HiddenSize == 0 || OutputSize == 0)
    {
        return 0.0;
    }

    // Prepare dataset: inputs = [Ia, Na, Ht], outputs = [Al, H]
    TArray<double> X; // flattened N x InputSize
    TArray<double> Y; // flattened N x OutputSize
    const int32 N = AuditoryDataEntries.Num();
    X.SetNumUninitialized(N * InputSize);
    Y.SetNumUninitialized(N * OutputSize);
    for (int32 n = 0; n < N; ++n)
    {
        const FAuditoryData& D = AuditoryDataEntries[n];
        X[n * InputSize + 0] = D.Ia;
        if (InputSize > 1) X[n * InputSize + 1] = D.Na;
        if (InputSize > 2) X[n * InputSize + 2] = D.Ht;

        Y[n * OutputSize + 0] = D.Al;
        if (OutputSize > 1) Y[n * OutputSize + 1] = D.H;
    }

    TArray<double> Z1, A1, Z2, A2;
    TArray<double> dW1, db1, dW2, db2;
    dW1.SetNumZeroed(W1.Num());
    db1.SetNumZeroed(b1.Num());
    dW2.SetNumZeroed(W2.Num());
    db2.SetNumZeroed(b2.Num());

    double FinalError = 0.0;

    for (int32 epoch = 0; epoch < Epochs; ++epoch)
    {
        // zero gradients
        FMemory::Memzero(dW1.GetData(), sizeof(double) * dW1.Num());
        FMemory::Memzero(db1.GetData(), sizeof(double) * db1.Num());
        FMemory::Memzero(dW2.GetData(), sizeof(double) * dW2.Num());
        FMemory::Memzero(db2.GetData(), sizeof(double) * db2.Num());

        double SumSqError = 0.0;

        // batch gradient over all samples
        for (int32 n = 0; n < N; ++n)
        {
            const double* x = &X[n * InputSize];
            const double* y = &Y[n * OutputSize];

            ForwardSingle(x, Z1, A1, Z2, A2);

            // Error and deltas at output
            TArray<double> dA2; dA2.SetNumUninitialized(OutputSize);
            for (int o = 0; o < OutputSize; ++o)
            {
                const double err = A2[o] - y[o];
                SumSqError += 0.5 * err * err;
                dA2[o] = err * SigmoidDerivFromActivation(A2[o]);
            }

            // Accumulate gradients for W2, b2
            for (int o = 0; o < OutputSize; ++o)
            {
                db2[o] += dA2[o];
                for (int h = 0; h < HiddenSize; ++h)
                {
                    dW2[W2Index(o, h, OutputSize, HiddenSize)] += dA2[o] * A1[h];
                }
            }

            // Backprop to hidden
            TArray<double> dA1; dA1.SetNumUninitialized(HiddenSize);
            for (int h = 0; h < HiddenSize; ++h)
            {
                double grad = 0.0;
                for (int o = 0; o < OutputSize; ++o)
                {
                    grad += dA2[o] * W2[W2Index(o, h, OutputSize, HiddenSize)];
                }
                dA1[h] = grad * SigmoidDerivFromActivation(A1[h]);
            }

            // Accumulate gradients for W1, b1
            for (int h = 0; h < HiddenSize; ++h)
            {
                db1[h] += dA1[h];
                for (int i = 0; i < InputSize; ++i)
                {
                    dW1[W1Index(h, i, HiddenSize, InputSize)] += dA1[h] * x[i];
                }
            }
        }

        // Average gradients and update
        const double InvN = 1.0 / FMath::Max(1, N);
        for (int i = 0; i < dW1.Num(); ++i) W1[i] -= LearningRate * dW1[i] * InvN;
        for (int i = 0; i < db1.Num(); ++i) b1[i] -= LearningRate * db1[i] * InvN;
        for (int i = 0; i < dW2.Num(); ++i) W2[i] -= LearningRate * dW2[i] * InvN;
        for (int i = 0; i < db2.Num(); ++i) b2[i] -= LearningRate * db2[i] * InvN;

        FinalError = SumSqError * InvN;

        if (epoch % 100 == 0)
        {
            UE_LOG(LogTemp, Log, TEXT("Epoch %d: Error = %f"), epoch, FinalError);
        }
    }

    return FinalError;
}

void UAttentionListeningAndHearingManager::PredictAuditoryResponse(double Ia, double Na, double Ht, double& OutAl, double& OutH) const
{
    if (InputSize == 0 || HiddenSize == 0 || OutputSize == 0)
    {
        OutAl = 0.0; OutH = 0.0; return;
    }

    double In[3] = { Ia, Na, Ht };
    TArray<double> Z1, A1, Z2, A2;
    ForwardSingle(In, Z1, A1, Z2, A2);

    OutAl = (OutputSize >= 1) ? A2[0] : 0.0;
    OutH  = (OutputSize >= 2) ? A2[1] : 0.0;
}

