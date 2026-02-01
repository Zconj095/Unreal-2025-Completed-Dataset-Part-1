// Converted from Unity C# to Unreal C++
#include "SystemAdministrationCreationSystem.h"

#include "Engine/World.h"
#include "TimerManager.h"

ASystemAdministrationCreationSystem::ASystemAdministrationCreationSystem()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASystemAdministrationCreationSystem::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(LogTemp, Log, TEXT("System Administration Creation System Initialized."));

    // Initial setup
    CreateObject(TEXT("Sphere"), FVector(0, 0, 0), FVector(1, 1, 1), TEXT("Solid"));
    CreateObject(TEXT("Cube"), FVector(2, 2, 2), FVector(1, 1, 1), TEXT("Hollow"));

    if (UWorld* World = GetWorld())
    {
        FTimerManager& TM = World->GetTimerManager();

        // Create objects every 5 seconds (delay 2s)
        TM.SetTimer(
            TimerHandle_AutoCreate,
            this,
            &ASystemAdministrationCreationSystem::AutoCreateObject,
            5.0f,
            true,
            2.0f);

        // Modify objects every 7 seconds (delay 3s)
        TM.SetTimer(
            TimerHandle_AutoModify,
            this,
            &ASystemAdministrationCreationSystem::AutoModifyObject,
            7.0f,
            true,
            3.0f);

        // Display objects every 10 seconds (delay 5s)
        TM.SetTimer(
            TimerHandle_Display,
            this,
            &ASystemAdministrationCreationSystem::DisplayObjects,
            10.0f,
            true,
            5.0f);
    }
}

void ASystemAdministrationCreationSystem::CreateObject(const FString& Name, const FVector& Position, const FVector& Scale, const FString& Value)
{
    FCreatorObject NewObject(Name, Position, Scale, Value);
    CreatedObjects.Add(NewObject);
    UE_LOG(LogTemp, Log, TEXT("Object Created - ID: %s, Name: %s, Value: %s"), *NewObject.ObjectID, *Name, *Value);
}

void ASystemAdministrationCreationSystem::ModifyObject(const FString& ObjectID, const FVector& NewPosition, const FVector& NewScale, const FString& NewValue)
{
    int32 Index = CreatedObjects.IndexOfByPredicate([&](const FCreatorObject& O){ return O.ObjectID == ObjectID; });
    if (Index != INDEX_NONE)
    {
        CreatedObjects[Index].UpdateTransform(NewPosition, NewScale);
        CreatedObjects[Index].UpdateValue(NewValue);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Object with ID '%s' not found."), *ObjectID);
    }
}

void ASystemAdministrationCreationSystem::DisplayObjects() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all created objects..."));
    for (const FCreatorObject& Obj : CreatedObjects)
    {
        Obj.Display();
    }
}

void ASystemAdministrationCreationSystem::AutoCreateObject()
{
    static const TArray<FString> ObjectNames = { TEXT("Pyramid"), TEXT("Cylinder"), TEXT("Prism"), TEXT("Torus") };
    static const TArray<FString> Values = { TEXT("Solid"), TEXT("Hollow"), TEXT("Liquid"), TEXT("Gas") };

    const int32 NameIdx = FMath::RandRange(0, ObjectNames.Num() - 1);
    const int32 ValueIdx = FMath::RandRange(0, Values.Num() - 1);

    const FVector Position(
        FMath::FRandRange(-10.f, 10.f),
        FMath::FRandRange(-10.f, 10.f),
        FMath::FRandRange(-10.f, 10.f));

    const FVector Scale(
        FMath::FRandRange(1.f, 3.f),
        FMath::FRandRange(1.f, 3.f),
        FMath::FRandRange(1.f, 3.f));

    CreateObject(ObjectNames[NameIdx], Position, Scale, Values[ValueIdx]);
}

void ASystemAdministrationCreationSystem::AutoModifyObject()
{
    if (CreatedObjects.Num() > 0)
    {
        const int32 Index = FMath::RandRange(0, CreatedObjects.Num() - 1);

        const FVector NewPosition(
            FMath::FRandRange(-10.f, 10.f),
            FMath::FRandRange(-10.f, 10.f),
            FMath::FRandRange(-10.f, 10.f));

        const FVector NewScale(
            FMath::FRandRange(1.f, 3.f),
            FMath::FRandRange(1.f, 3.f),
            FMath::FRandRange(1.f, 3.f));

        const FString NewValue = (FMath::RandRange(0, 1) == 0) ? TEXT("Plasma") : TEXT("Energy");

        ModifyObject(CreatedObjects[Index].ObjectID, NewPosition, NewScale, NewValue);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No objects available to modify."));
    }
}

