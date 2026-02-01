// Converted from Unity CortexCogniEnigma MonoBehaviour to Unreal ActorComponent.
#include "CortexCogniEnigmaComponent.h"
#include "GameFramework/Actor.h"

#include "Components/MeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/OverlapResult.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

UCortexCogniEnigmaComponent::UCortexCogniEnigmaComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UCortexCogniEnigmaComponent::BeginPlay()
{
    Super::BeginPlay();

    InitializeRenderer();
    if (TargetRenderer && DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue(TEXT("Color"), DormantColor);
    }

    GetWorld()->GetTimerManager().SetTimer(
        AnalysisTimerHandle,
        this,
        &UCortexCogniEnigmaComponent::AnalyzeEnvironment,
        AnalysisInterval,
        true,
        0.5f);
}

void UCortexCogniEnigmaComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(AnalysisTimerHandle);
    }

    Super::EndPlay(EndPlayReason);
}

void UCortexCogniEnigmaComponent::InitializeRenderer()
{
    if (AActor* Owner = GetOwner())
    {
        TargetRenderer = Owner->FindComponentByClass<UPrimitiveComponent>();
        if (TargetRenderer)
        {
            if (UMaterialInterface* Material = TargetRenderer->GetMaterial(0))
            {
                DynamicMaterial = TargetRenderer->CreateDynamicMaterialInstance(0, Material);
            }
        }
    }
}

void UCortexCogniEnigmaComponent::AnalyzeEnvironment()
{
    if (!EnvironmentSource && !GetOwner())
    {
        return;
    }

    const FString Stimuli = DetectStimuli();
    if (Stimuli.IsEmpty())
    {
        UpdateAppearance(0.0f);
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("Stimuli detected: %s"), *Stimuli);
    ProcessStimuli(Stimuli);
}

FString UCortexCogniEnigmaComponent::DetectStimuli() const
{
    const FVector Origin = EnvironmentSource ? EnvironmentSource->GetActorLocation() : GetOwner()->GetActorLocation();
    TArray<FOverlapResult> Results;

    FCollisionShape Sphere = FCollisionShape::MakeSphere(DetectionRadius);
    GetWorld()->OverlapMultiByChannel(
        Results,
        Origin,
        FQuat::Identity,
        ECC_WorldStatic,
        Sphere);

    if (Results.Num() == 0)
    {
        return FString();
    }

    FString Signature;
    for (const FOverlapResult& Result : Results)
    {
        if (AActor* Actor = Result.GetActor())
        {
            Signature += Actor->GetName() + TEXT("-");
        }
    }

    Signature.RemoveFromEnd(TEXT("-"));
    return Signature;
}

void UCortexCogniEnigmaComponent::ProcessStimuli(const FString& Stimuli)
{
    float& PathStrength = NeuralPathways.FindOrAdd(Stimuli);
    if (PathStrength == 0.0f)
    {
        PathStrength = FMath::FRandRange(0.1f, 1.0f);
        Memory.Add(Stimuli);
    }
    else
    {
        PathStrength += 0.1f;
    }

    Adapt(Stimuli);
    UpdateAppearance(PathStrength);
}

void UCortexCogniEnigmaComponent::Adapt(const FString& Stimuli)
{
    float* StrengthPtr = NeuralPathways.Find(Stimuli);
    if (!StrengthPtr)
    {
        return;
    }

    if (*StrengthPtr >= AdaptationThreshold)
    {
        UE_LOG(LogTemp, Log, TEXT("Enigma solved: Adapted to %s"), *Stimuli);
        *StrengthPtr = 0.1f;
    }
}

void UCortexCogniEnigmaComponent::UpdateAppearance(float Intensity)
{
    const float Clamped = FMath::Clamp(Intensity, 0.0f, 1.0f);
    const FLinearColor Target = FLinearColor::LerpUsingHSV(DormantColor, ActiveColor, Clamped);
    if (DynamicMaterial)
    {
        DynamicMaterial->SetVectorParameterValue(TEXT("Color"), Target);
    }
    else if (TargetRenderer)
    {
        if (UMeshComponent* Mesh = Cast<UMeshComponent>(TargetRenderer))
        {
            Mesh->SetVectorParameterValueOnMaterials(TEXT("BaseColor"), FVector(Target.R, Target.G, Target.B));
        }
    }
}
