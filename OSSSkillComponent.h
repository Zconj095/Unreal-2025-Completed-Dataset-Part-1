// Component that lets a player learn "Sword Skill Creation", create OSS skills, assign hotkeys, and execute/practice them
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OSSSkillTypes.h"
#include "OSSSkillComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOSSSkillEvent, const FOSSSkillDefinition&, Skill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOSSMoveEvent, int32, MoveIndex, const FOSSMove&, Move);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOSSPracticeEvent, bool, bIsPracticeMode);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PEKBGGAP_API UOSSSkillComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UOSSSkillComponent();

    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Learning gate
    UFUNCTION(BlueprintCallable, Category="OSS|Learning")
    void LearnSwordSkillCreation() { bHasSwordSkillCreation = true; }

    UFUNCTION(BlueprintPure, Category="OSS|Learning")
    bool HasSwordSkillCreation() const { return bHasSwordSkillCreation; }

    // CRUD
    UFUNCTION(BlueprintCallable, Category="OSS|Skills")
    int32 AddSkill(const FOSSSkillDefinition& Definition);

    UFUNCTION(BlueprintCallable, Category="OSS|Skills")
    bool RemoveSkillByName(FName SkillName);

    UFUNCTION(BlueprintPure, Category="OSS|Skills")
    bool GetSkillByName(FName SkillName, FOSSSkillDefinition& Out) const;

    UFUNCTION(BlueprintCallable, Category="OSS|Hotbar")
    void AssignHotkey(int32 Slot, FName SkillName);

    UFUNCTION(BlueprintCallable, Category="OSS|Hotbar")
    bool UseSkillByHotkey(int32 Slot, bool bPractice = false);

    UFUNCTION(BlueprintCallable, Category="OSS|Practice")
    bool PracticeSkillByName(FName SkillName) { return ActivateSkillByName(SkillName, true); }

    UFUNCTION(BlueprintCallable, Category="OSS|Practice")
    void SetInSafeArea(bool bInSafe) { bInSafeArea = bInSafe; }

    // Events
    UPROPERTY(BlueprintAssignable, Category="OSS|Events")
    FOSSSkillEvent OnSkillStarted;

    UPROPERTY(BlueprintAssignable, Category="OSS|Events")
    FOSSSkillEvent OnSkillCompleted;

    UPROPERTY(BlueprintAssignable, Category="OSS|Events")
    FOSSMoveEvent OnMoveStarted;

    UPROPERTY(BlueprintAssignable, Category="OSS|Events")
    FOSSMoveEvent OnMoveEnded;

    UPROPERTY(BlueprintAssignable, Category="OSS|Events")
    FOSSPracticeEvent OnPracticeModeChanged;

    // Runtime state
    UPROPERTY(BlueprintReadOnly, Category="OSS|Runtime")
    bool bIsExecuting = false;

    UPROPERTY(BlueprintReadOnly, Category="OSS|Runtime")
    bool bPracticeMode = false;

private:
    bool ActivateSkillByName(FName SkillName, bool bPractice);
    void StepExecution(float DeltaTime);
    void FireEffectsForMove(const FOSSMove& Move);

private:
    UPROPERTY()
    bool bHasSwordSkillCreation = false;

    UPROPERTY()
    TArray<FOSSSkillDefinition> Skills;

    // Hotbar slots -> index in Skills array
    UPROPERTY()
    TMap<int32, int32> Hotbar;

    // Execution bookkeeping
    int32 ActiveSkillIndex = INDEX_NONE;
    int32 CurrentMoveIndex = INDEX_NONE;
    float MoveTimeRemaining = 0.0f;
    float CooldownRemaining = 0.0f;

    bool bInSafeArea = true; // practice allowed regardless; combat effects suppressed in safe areas
};

