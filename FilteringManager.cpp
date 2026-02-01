#include "FilteringManager.h"
#include "Math/UnrealMathUtility.h"

namespace
{
    FORCEINLINE int W1Index(int r, int c, int Hidden, int Input) { return r * Input + c; }
    FORCEINLINE int W2Index(int r, int c, int Output, int Hidden) { return r * Hidden + c; }
}

double UFilteringManager::Sigmoid(double x)
{
    x = FMath::Clamp(x, -50.0, 50.0);
    return 1.0 / (1.0 + FMath::Exp(-x));
}

double UFilteringManager::SigmoidDerivFromActivation(double a)
{
    return a * (1.0 - a);
}

void UFilteringManager::RandomizeParams(double Scale)
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

void UFilteringManager::InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize)
{
    InputSize = InInputSize;
    HiddenSize = InHiddenNeurons;
    OutputSize = InOutputSize;
    RandomizeParams(0.1);
}

void UFilteringManager::ForwardSingle(const double* InX, TArray<double>& Z1, TArray<double>& A1, TArray<double>& Z2, TArray<double>& A2) const
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

void UFilteringManager::TrainNetwork(const TArray<FDoubleArray>& Inputs, const TArray<FDoubleArray>& Outputs, int32 Epochs, double LearningRate)
{
    const int32 N = Inputs.Num();
    if (N == 0 || Outputs.Num() != N || InputSize == 0 || HiddenSize == 0 || OutputSize == 0)
    {
        return;
    }

    // Flatten into contiguous buffers
    TArray<double> X; X.SetNumZeroed(N * InputSize);
    TArray<double> Y; Y.SetNumZeroed(N * OutputSize);
    for (int32 n = 0; n < N; ++n)
    {
        const TArray<double>& xi = Inputs[n].Values;
        const TArray<double>& yi = Outputs[n].Values;
        for (int i = 0; i < InputSize && i < xi.Num(); ++i) X[n * InputSize + i] = xi[i];
        for (int o = 0; o < OutputSize && o < yi.Num(); ++o) Y[n * OutputSize + o] = yi[o];
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

double UFilteringManager::Predict(const TArray<double>& Input) const
{
    if (InputSize == 0 || HiddenSize == 0 || OutputSize == 0) return 0.0;

    TArray<double> X; X.SetNumZeroed(InputSize);
    for (int i = 0; i < InputSize && i < Input.Num(); ++i) X[i] = Input[i];

    TArray<double> Z1, A1, Z2, A2;
    ForwardSingle(X.GetData(), Z1, A1, Z2, A2);
    return A2[0];
}

TArray<double> UFilteringManager::Filter(const TArray<double>& Data, TFunctionRef<bool(double)> Predicate) const
{
    TArray<double> Out;
    for (double v : Data)
    {
        if (Predicate(v)) Out.Add(v);
    }
    return Out;
}

void UFilteringManager::AddFilteringData(const TArray<double>& Data, TFunctionRef<bool(double)> Predicate)
{
    const TArray<double> Filtered = Filter(Data, Predicate);
    FilteredDataEntries.Add(FFilteredData(Data, Filtered));
}

void UFilteringManager::DisplayFilteredResults() const
{
    for (const FFilteredData& E : FilteredDataEntries)
    {
        FString Orig;
        for (int i = 0; i < E.OriginalData.Num(); ++i)
        {
            if (i) Orig += TEXT(", ");
            Orig += FString::SanitizeFloat(E.OriginalData[i]);
        }

        FString Fil;
        for (int i = 0; i < E.FilteredResults.Num(); ++i)
        {
            if (i) Fil += TEXT(", ");
            Fil += FString::SanitizeFloat(E.FilteredResults[i]);
        }

        UE_LOG(LogTemp, Log, TEXT("Original Data: %s"), *Orig);
        UE_LOG(LogTemp, Log, TEXT("Filtered Results: %s"), *Fil);
    }
}
