#include "TemporalLSTMManager.h"
#include "Math/UnrealMathUtility.h"

namespace
{
    FORCEINLINE int W1Index(int r, int c, int Hidden, int Input) { return r * Input + c; }
    FORCEINLINE int W2Index(int r, int c, int Output, int Hidden) { return r * Hidden + c; }
}

double UTemporalLSTMManager::Sigmoid(double x)
{
    x = FMath::Clamp(x, -50.0, 50.0);
    return 1.0 / (1.0 + FMath::Exp(-x));
}

double UTemporalLSTMManager::SigmoidDerivFromActivation(double a)
{
    return a * (1.0 - a);
}

void UTemporalLSTMManager::RandomizeParams(double Scale)
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

void UTemporalLSTMManager::InitializeLSTM(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize)
{
    InputSize = InInputSize;
    HiddenSize = InHiddenNeurons;
    OutputSize = InOutputSize; // e.g., 1
    RandomizeParams(0.1);
}

void UTemporalLSTMManager::AddTemporalData(const TArray<double>& TimeSeriesInput, const TArray<double>& ExpectedOutput)
{
    Entries.Add(FTemporalData(TimeSeriesInput, ExpectedOutput));
}

void UTemporalLSTMManager::ForwardSingle(const double* InX, TArray<double>& Z1, TArray<double>& A1, TArray<double>& Z2, TArray<double>& A2) const
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

double UTemporalLSTMManager::TrainLSTM(int32 Epochs, double LearningRate)
{
    if (Entries.Num() == 0 || InputSize == 0 || HiddenSize == 0 || OutputSize == 0)
    {
        return 0.0;
    }

    const int32 N = Entries.Num();
    TArray<double> X; X.SetNumZeroed(N * InputSize);
    TArray<double> Y; Y.SetNumZeroed(N * OutputSize);

    for (int32 n = 0; n < N; ++n)
    {
        const FTemporalData& D = Entries[n];
        for (int i = 0; i < InputSize; ++i)
        {
            X[n * InputSize + i] = (i < D.TimeSeriesInput.Num()) ? D.TimeSeriesInput[i] : 0.0;
        }
        for (int o = 0; o < OutputSize; ++o)
        {
            Y[n * OutputSize + o] = (o < D.ExpectedOutput.Num()) ? D.ExpectedOutput[o] : 0.0;
        }
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

            // Output layer delta (MSE + sigmoid)
            TArray<double> dA2; dA2.SetNumUninitialized(OutputSize);
            for (int o = 0; o < OutputSize; ++o)
            {
                const double err = A2[o] - y[o];
                SumSqError += 0.5 * err * err;
                dA2[o] = err * SigmoidDerivFromActivation(A2[o]);
            }

            // Gradients W2, b2
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

            // Gradients W1, b1
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

        FinalError = SumSqError * InvN;
        if (epoch % 100 == 0)
        {
            UE_LOG(LogTemp, Log, TEXT("Epoch %d: Error = %f"), epoch, FinalError);
        }
    }

    return FinalError;
}

TArray<double> UTemporalLSTMManager::Predict(const TArray<double>& TimeSeriesInput) const
{
    TArray<double> In; In.SetNumZeroed(InputSize);
    for (int i = 0; i < InputSize && i < TimeSeriesInput.Num(); ++i)
    {
        In[i] = TimeSeriesInput[i];
    }
    TArray<double> Z1, A1, Z2, A2;
    ForwardSingle(In.GetData(), Z1, A1, Z2, A2);

    TArray<double> Out; Out.SetNumUninitialized(OutputSize);
    for (int o = 0; o < OutputSize; ++o) Out[o] = A2[o];
    return Out;
}

double UTemporalLSTMManager::CalculateAveragePredictionError(const TArray<FDoubleArray>& TestInputs, const TArray<FDoubleArray>& TestOutputs) const
{
    if (TestInputs.Num() != TestOutputs.Num())
    {
        UE_LOG(LogTemp, Error, TEXT("CalculateAveragePredictionError: Input and output counts must match."));
        return 0.0;
    }
    if (TestInputs.Num() == 0) return 0.0;

    double SumErr = 0.0;
    const int32 N = TestInputs.Num();
    for (int32 i = 0; i < N; ++i)
    {
        const TArray<double> Pred = Predict(TestInputs[i].Values);
        const TArray<double>& Target = TestOutputs[i].Values;
        if (Pred.Num() != Target.Num())
        {
            UE_LOG(LogTemp, Warning, TEXT("Sample %d: prediction/target size mismatch (%d vs %d)."), i, Pred.Num(), Target.Num());
        }
        const int32 M = FMath::Min(Pred.Num(), Target.Num());
        double SumSq = 0.0;
        for (int32 k = 0; k < M; ++k)
        {
            const double d = Target[k] - Pred[k];
            SumSq += d * d;
        }
        SumErr += FMath::Sqrt(SumSq);
    }
    return SumErr / static_cast<double>(N);
}
