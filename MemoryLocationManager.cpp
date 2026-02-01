#include "MemoryLocationManager.h"
#include "Math/UnrealMathUtility.h"

namespace
{
    FORCEINLINE int W1Index(int r, int c, int Hidden, int Input) { return r * Input + c; }
    FORCEINLINE int W2Index(int r, int c, int Output, int Hidden) { return r * Hidden + c; }
}

double UMemoryLocationManager::Sigmoid(double x)
{
    x = FMath::Clamp(x, -50.0, 50.0);
    return 1.0 / (1.0 + FMath::Exp(-x));
}

double UMemoryLocationManager::SigmoidDerivFromActivation(double a)
{
    return a * (1.0 - a);
}

void UMemoryLocationManager::RandomizeParams(double Scale)
{
    W1.SetNumZeroed(HiddenSize * InputSize);
    b1.SetNumZeroed(HiddenSize);
    W2.SetNumZeroed(OutputSize * HiddenSize);
    b2.SetNumZeroed(OutputSize);

    for (int i = 0; i < W1.Num(); ++i) W1[i] = FMath::FRandRange(-Scale, Scale);
    for (int i = 0; i < b1.Num(); ++i) b1[i] = 0.0;
    for (int i = 0; i < W2.Num(); ++i) W2[i] = FMath::FRandRange(-Scale, Scale);
    for (int i = 0; i < b2.Num(); ++i) b2[i] = 0.0;
}

void UMemoryLocationManager::InitializeNeuralNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize)
{
    InputSize = InInputSize;
    HiddenSize = InHiddenNeurons;
    OutputSize = InOutputSize; // e.g., 2
    RandomizeParams(0.1);
}

void UMemoryLocationManager::AddMemoryLocation(const FString& Id, const FVector2D& Location, const TArray<double>& Features, bool bIsAccessed)
{
    Entries.Add(FMemoryLocationEntry(Id, Location, Features, bIsAccessed));
}

double UMemoryLocationManager::CalculateAccessRate() const
{
    if (Entries.Num() == 0) return 0.0;
    int32 Accessed = 0;
    for (const FMemoryLocationEntry& E : Entries)
    {
        if (E.bIsAccessed) ++Accessed;
    }
    return static_cast<double>(Accessed) / static_cast<double>(Entries.Num());
}

FVector2D UMemoryLocationManager::CalculateAverageLocation() const
{
    if (Entries.Num() == 0) return FVector2D::ZeroVector;
    double X = 0.0, Y = 0.0;
    for (const FMemoryLocationEntry& E : Entries)
    {
        X += E.Location.X;
        Y += E.Location.Y;
    }
    const double N = static_cast<double>(Entries.Num());
    return FVector2D(X / N, Y / N);
}

void UMemoryLocationManager::ForwardSingle(const double* InX, TArray<double>& Z1, TArray<double>& A1, TArray<double>& Z2, TArray<double>& A2) const
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

void UMemoryLocationManager::TrainNetwork(int32 Epochs, double LearningRate)
{
    if (Entries.Num() == 0 || InputSize == 0 || HiddenSize == 0 || OutputSize == 0) return;

    const int32 N = Entries.Num();
    TArray<double> X; X.SetNumZeroed(N * InputSize);
    TArray<double> Y; Y.SetNumZeroed(N * OutputSize);

    // Use access flag as target for all outputs (simple placeholder to drive outputs > 0 when accessed)
    for (int32 n = 0; n < N; ++n)
    {
        const FMemoryLocationEntry& E = Entries[n];
        for (int i = 0; i < InputSize && i < E.Features.Num(); ++i) X[n * InputSize + i] = E.Features[i];
        const double t = E.bIsAccessed ? 1.0 : 0.0;
        for (int o = 0; o < OutputSize; ++o) Y[n * OutputSize + o] = t;
    }

    TArray<double> Z1, A1, Z2, A2;
    TArray<double> dW1, db1, dW2, db2;
    dW1.SetNumZeroed(W1.Num());
    db1.SetNumZeroed(b1.Num());
    dW2.SetNumZeroed(W2.Num());
    db2.SetNumZeroed(b2.Num());

    for (int32 epoch = 0; epoch < Epochs; ++epoch)
    {
        FMemory::Memzero(dW1.GetData(), sizeof(double) * dW1.Num());
        FMemory::Memzero(db1.GetData(), sizeof(double) * db1.Num());
        FMemory::Memzero(dW2.GetData(), sizeof(double) * dW2.Num());
        FMemory::Memzero(db2.GetData(), sizeof(double) * db2.Num());

        double SumSqError = 0.0;

        for (int32 n = 0; n < N; ++n)
        {
            const double* x = &X[n * InputSize];
            const double* y = &Y[n * OutputSize];

            ForwardSingle(x, Z1, A1, Z2, A2);

            TArray<double> dA2; dA2.SetNumUninitialized(OutputSize);
            for (int o = 0; o < OutputSize; ++o)
            {
                const double err = A2[o] - y[o];
                SumSqError += 0.5 * err * err;
                dA2[o] = err * SigmoidDerivFromActivation(A2[o]);
            }

            for (int o = 0; o < OutputSize; ++o)
            {
                db2[o] += dA2[o];
                for (int h = 0; h < HiddenSize; ++h)
                {
                    dW2[W2Index(o, h, OutputSize, HiddenSize)] += dA2[o] * A1[h];
                }
            }

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

            for (int h = 0; h < HiddenSize; ++h)
            {
                db1[h] += dA1[h];
                for (int i = 0; i < InputSize; ++i)
                {
                    dW1[W1Index(h, i, HiddenSize, InputSize)] += dA1[h] * x[i];
                }
            }
        }

        const double InvN = 1.0 / FMath::Max(1, N);
        for (int i = 0; i < dW1.Num(); ++i) W1[i] -= LearningRate * dW1[i] * InvN;
        for (int i = 0; i < db1.Num(); ++i) b1[i] -= LearningRate * db1[i] * InvN;
        for (int i = 0; i < dW2.Num(); ++i) W2[i] -= LearningRate * dW2[i] * InvN;
        for (int i = 0; i < db2.Num(); ++i) b2[i] -= LearningRate * db2[i] * InvN;

        if (epoch % 100 == 0)
        {
            UE_LOG(LogTemp, Log, TEXT("Epoch %d: Error = %f"), epoch, SumSqError * InvN);
        }
    }
}

FVector2D UMemoryLocationManager::PredictOptimalLocation(const TArray<double>& Features) const
{
    FVector2D Result(0.0, 0.0);
    if (InputSize == 0 || HiddenSize == 0 || OutputSize == 0) return Result;

    TArray<double> X; X.SetNumZeroed(InputSize);
    for (int i = 0; i < InputSize && i < Features.Num(); ++i) X[i] = Features[i];

    TArray<double> Z1, A1, Z2, A2;
    ForwardSingle(X.GetData(), Z1, A1, Z2, A2);

    const double Scale = 10.0; // mimic Unity scaling
    const double Xout = (OutputSize >= 1) ? A2[0] * Scale : 0.0;
    const double Yout = (OutputSize >= 2) ? A2[1] * Scale : 0.0;
    return FVector2D(Xout, Yout);
}

