// Converted from Unity C# to Unreal C++
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SystemAdministrationCreationSystem.generated.h"

USTRUCT(BlueprintType)
struct FCreatorObject
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SystemAdmin|Creation")
    FString ObjectID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Creation")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Creation")
    FVector Position = FVector::ZeroVector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Creation")
    FVector Scale = FVector(1.f, 1.f, 1.f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SystemAdmin|Creation")
    FString Value; // Defines the existence of the object

    FCreatorObject() {}
    FCreatorObject(const FString& InName, const FVector& InPosition, const FVector& InScale, const FString& InValue)
        : ObjectID(FGuid::NewGuid().ToString())
        , Name(InName)
        , Position(InPosition)
        , Scale(InScale)
        , Value(InValue)
    {}

    void UpdateValue(const FString& NewValue)
    {
        Value = NewValue;
        UE_LOG(LogTemp, Log, TEXT("Object '%s' updated with new value: %s"), *Name, *Value);
    }

    void UpdateTransform(const FVector& NewPosition, const FVector& NewScale)
    {
        Position = NewPosition;
        Scale = NewScale;
        UE_LOG(LogTemp, Log, TEXT("Object '%s' updated to Position: %s, Scale: %s"), *Name, *Position.ToString(), *Scale.ToString());
    }

    void Display() const
    {
        UE_LOG(LogTemp, Log, TEXT("Object ID: %s, Name: %s, Position: %s, Scale: %s, Value: %s"), *ObjectID, *Name, *Position.ToString(), *Scale.ToString(), *Value);
    }
};

UCLASS()
class PEKBGGAP_API ASystemAdministrationCreationSystem : public AActor
{
    GENERATED_BODY()

public:
    ASystemAdministrationCreationSystem();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Creation")
    void CreateObject(const FString& Name, const FVector& Position, const FVector& Scale, const FString& Value);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Creation")
    void ModifyObject(const FString& ObjectID, const FVector& NewPosition, const FVector& NewScale, const FString& NewValue);

    UFUNCTION(BlueprintCallable, Category = "SystemAdmin|Creation")
    void DisplayObjects() const;

private:
    // Data
    UPROPERTY()
    TArray<FCreatorObject> CreatedObjects;

    // Timers
    FTimerHandle TimerHandle_AutoCreate;
    FTimerHandle TimerHandle_AutoModify;
    FTimerHandle TimerHandle_Display;

    // Auto helpers
    void AutoCreateObject();
    void AutoModifyObject();
};

