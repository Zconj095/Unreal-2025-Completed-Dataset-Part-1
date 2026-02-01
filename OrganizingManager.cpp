#include "OrganizingManager.h"
#include "Math/UnrealMathUtility.h"

namespace
{
    FORCEINLINE int W1Index(int r, int c, int Hidden, int Input) { return r * Input + c; }
    FORCEINLINE int W2Index(int r, int c, int Output, int Hidden) { return r * Hidden + c; }
}

double UOrganizingManager::Sigmoid(double x)
{
    x = FMath::Clamp(x, -50.0, 50.0);
    return 1.0 / (1.0 + FMath::Exp(-x));
}

double UOrganizingManager::SigmoidDerivFromActivation(double a)
{
    return a * (1.0 - a);
}

void UOrganizingManager::RandomizeParams(double Scale)
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

void UOrganizingManager::InitializeNetwork(int32 InInputSize, int32 InHiddenNeurons, int32 InOutputSize)
{
    InputSize = InInputSize;
    HiddenSize = InHiddenNeurons;
    OutputSize = InOutputSize; // number of classes
    RandomizeParams(0.1);
}

FDataGroup* UOrganizingManager::FindOrAddGroup(int32 GroupID)
{
    for (FDataGroup& G : Groups)
    {
        if (G.GroupID == GroupID) return &G;
    }
    Groups.Add(FDataGroup(GroupID));
    return &Groups.Last();
}

void UOrganizingManager::OrganizeData(const TArray<FDoubleArray>& Data, const TArray<int32>& GroupIDs)
{
    const int32 N = Data.Num();
    if (GroupIDs.Num() != N)
    {
        UE_LOG(LogTemp, Warning, TEXT("OrganizeData: GroupIDs size (%d) != Data size (%d)."), GroupIDs.Num(), N);
    }
    const int32 M = FMath::Min(N, GroupIDs.Num());
    for (int32 i = 0; i < M; ++i)
    {
        FDataGroup* G = FindOrAddGroup(GroupIDs[i]);
        if (G)
        {
            G->Items.Add(Data[i]);
        }
    }
}

void UOrganizingManager::AddDataToGroups(const TArray<double>& Item, int32 GroupID)
{
    FDataGroup* G = FindOrAddGroup(GroupID);
    if (G)
    {
        FDoubleArray Wrap; Wrap.Values = Item; G->Items.Add(MoveTemp(Wrap));
    }
}

void UOrganizingManager::ForwardSingle(const double* InX, TArray<double>& Z1, TArray<double>& A1, TArray<double>& Z2, TArray<double>& A2) const
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

void UOrganizingManager::TrainNetwork(const TArray<FDoubleArray>& Inputs, const TArray<int32>& GroupIDs, int32 Epochs, double LearningRate)
{
    const int32 N = Inputs.Num();
    if (N == 0 || InputSize == 0 || HiddenSize == 0 || OutputSize == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("TrainNetwork: invalid dimensions or empty dataset."));
        return;
    }
    if (GroupIDs.Num() != N)
    {
        UE_LOG(LogTemp, Warning, TEXT("TrainNetwork: GroupIDs size (%d) != Inputs size (%d)."), GroupIDs.Num(), N);
    }
    // Check labels within range
    for (int32 n = 0; n < GroupIDs.Num(); ++n)
    {
        if (GroupIDs[n] < 0 || GroupIDs[n] >= OutputSize)
        {
            UE_LOG(LogTemp, Warning, TEXT("TrainNetwork: label %d out of range [0, %d)."), GroupIDs[n], OutputSize);
        }
    }

    // Flatten inputs and build one-hot outputs
    TArray<double> X; X.SetNumZeroed(N * InputSize);
    TArray<double> Y; Y.SetNumZeroed(N * OutputSize);
    for (int32 n = 0; n < N; ++n)
    {
        const TArray<double>& sample = Inputs[n].Values;
        for (int i = 0; i < InputSize; ++i)
        {
            X[n * InputSize + i] = (i < sample.Num()) ? sample[i] : 0.0;
        }
        const int32 label = (n < GroupIDs.Num()) ? GroupIDs[n] : 0;
        if (label >= 0 && label < OutputSize)
        {
            Y[n * OutputSize + label] = 1.0;
        }
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

            // Output deltas (MSE + sigmoid)
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

            // Backprop hidden
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

        const double FinalError = SumSqError * InvN;
        if (epoch % 100 == 0)
        {
            UE_LOG(LogTemp, Log, TEXT("Epoch %d: Error = %f"), epoch, FinalError);
        }
    }
}

int32 UOrganizingManager::PredictGroup(const TArray<double>& Data) const
{
    if (InputSize == 0 || HiddenSize == 0 || OutputSize == 0)
    {
        return 0;
    }
    TArray<double> In; In.SetNumZeroed(InputSize);
    for (int i = 0; i < InputSize && i < Data.Num(); ++i)
    {
        In[i] = Data[i];
    }
    TArray<double> Z1, A1, Z2, A2;
    ForwardSingle(In.GetData(), Z1, A1, Z2, A2);
    int32 ArgMax = 0; double Best = A2[0];
    for (int32 o = 1; o < OutputSize; ++o)
    {
        if (A2[o] > Best) { Best = A2[o]; ArgMax = o; }
    }
    return ArgMax;
}

void UOrganizingManager::DisplayGroups() const
{
    for (const FDataGroup& G : Groups)
    {
        UE_LOG(LogTemp, Log, TEXT("Group %d: %d items"), G.GroupID, G.Items.Num());
        for (const FDoubleArray& Item : G.Items)
        {
            FString Line;
            for (int i = 0; i < Item.Values.Num(); ++i)
            {
                Line += FString::SanitizeFloat(Item.Values[i]);
                if (i + 1 < Item.Values.Num()) Line += TEXT(", ");
            }
            UE_LOG(LogTemp, Log, TEXT("  Item: %s"), *Line);
        }
    }
}
