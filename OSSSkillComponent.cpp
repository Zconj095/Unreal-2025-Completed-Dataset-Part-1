#include "OSSSkillComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"

UOSSSkillComponent::UOSSSkillComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UOSSSkillComponent::BeginPlay()
{
    Super::BeginPlay();
}

int32 UOSSSkillComponent::AddSkill(const FOSSSkillDefinition& Definition)
{
    if (!bHasSwordSkillCreation) { return INDEX_NONE; }
    const int32 Idx = Skills.Add(Definition);
    return Idx;
}

bool UOSSSkillComponent::RemoveSkillByName(FName SkillName)
{
    for (int32 i = 0; i < Skills.Num(); ++i)
    {
        if (Skills[i].SkillName == SkillName)
        {
            Skills.RemoveAt(i);
            // Fix hotbar mappings
            for (auto& Pair : Hotbar)
            {
                if (Pair.Value == i) { Pair.Value = INDEX_NONE; }
                else if (Pair.Value > i) { Pair.Value--; }
            }
            return true;
        }
    }
    return false;
}

bool UOSSSkillComponent::GetSkillByName(FName SkillName, FOSSSkillDefinition& Out) const
{
    for (const auto& S : Skills)
    {
        if (S.SkillName == SkillName) { Out = S; return true; }
    }
    return false;
}

void UOSSSkillComponent::AssignHotkey(int32 Slot, FName SkillName)
{
    for (int32 i = 0; i < Skills.Num(); ++i)
    {
        if (Skills[i].SkillName == SkillName)
        {
            Hotbar.Add(Slot, i);
            return;
        }
    }
}

bool UOSSSkillComponent::UseSkillByHotkey(int32 Slot, bool bPractice)
{
    if (!Hotbar.Contains(Slot)) { return false; }
    const int32* Idx = Hotbar.Find(Slot);
    if (!Idx || *Idx == INDEX_NONE || !Skills.IsValidIndex(*Idx)) { return false; }
    return ActivateSkillByName(Skills[*Idx].SkillName, bPractice);
}

bool UOSSSkillComponent::ActivateSkillByName(FName SkillName, bool bPractice)
{
    if (bIsExecuting || CooldownRemaining > 0.0f) { return false; }
    for (int32 i = 0; i < Skills.Num(); ++i)
    {
        if (Skills[i].SkillName == SkillName)
        {
            ActiveSkillIndex = i;
            CurrentMoveIndex = 0;
            MoveTimeRemaining = (Skills[i].Moves.Num() > 0) ? Skills[i].Moves[0].Duration : 0.0f;
            bIsExecuting = true;
            bPracticeMode = bPractice;
            OnPracticeModeChanged.Broadcast(bPracticeMode);
            OnSkillStarted.Broadcast(Skills[i]);
            if (Skills[i].Moves.Num() > 0)
            {
                OnMoveStarted.Broadcast(CurrentMoveIndex, Skills[i].Moves[0]);
                FireEffectsForMove(Skills[i].Moves[0]);
            }
            return true;
        }
    }
    return false;
}

void UOSSSkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    StepExecution(DeltaTime);
}

void UOSSSkillComponent::StepExecution(float DeltaTime)
{
    if (CooldownRemaining > 0.0f)
    {
        CooldownRemaining = FMath::Max(0.0f, CooldownRemaining - DeltaTime);
    }

    if (!bIsExecuting || !Skills.IsValidIndex(ActiveSkillIndex)) { return; }

    if (CurrentMoveIndex == INDEX_NONE)
    {
        // Safety bailout
        bIsExecuting = false; ActiveSkillIndex = INDEX_NONE; return;
    }

    MoveTimeRemaining -= DeltaTime;
    if (MoveTimeRemaining > 0.0f) { return; }

    // End current move
    const FOSSSkillDefinition& Skill = Skills[ActiveSkillIndex];
    OnMoveEnded.Broadcast(CurrentMoveIndex, Skill.Moves[CurrentMoveIndex]);

    // Advance
    CurrentMoveIndex++;
    if (CurrentMoveIndex >= Skill.Moves.Num())
    {
        // Done
        bIsExecuting = false;
        CooldownRemaining = Skill.Cooldown;
        OnSkillCompleted.Broadcast(Skill);
        ActiveSkillIndex = INDEX_NONE;
        CurrentMoveIndex = INDEX_NONE;
        return;
    }

    MoveTimeRemaining = Skill.Moves[CurrentMoveIndex].Duration;
    OnMoveStarted.Broadcast(CurrentMoveIndex, Skill.Moves[CurrentMoveIndex]);
    FireEffectsForMove(Skill.Moves[CurrentMoveIndex]);
}

void UOSSSkillComponent::FireEffectsForMove(const FOSSMove& Move)
{
    if (!GetOwner()) { return; }
    const FOSSSpecialEffect& FX = Move.Effect;
    if (FX.Particle)
    {
        USceneComponent* AttachTo = GetOwner()->GetRootComponent();
        if (AttachTo && !FX.AttachSocket.IsNone())
        {
            if (USkeletalMeshComponent* Skel = Cast<USkeletalMeshComponent>(AttachTo))
            {
                UGameplayStatics::SpawnEmitterAttached(FX.Particle, Skel, FX.AttachSocket);
            }
            else
            {
                UGameplayStatics::SpawnEmitterAttached(FX.Particle, AttachTo);
            }
        }
        else if (AttachTo)
        {
            UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), FX.Particle, AttachTo->GetComponentTransform());
        }
    }
    if (FX.Sound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FX.Sound, GetOwner()->GetActorLocation());
    }
}

