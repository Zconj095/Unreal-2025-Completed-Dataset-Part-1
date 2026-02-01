#include "MatrixWisdomUse.h"
#include "Engine/World.h"

#include "Misc/Guid.h"
#include "TimerManager.h"

AMatrixWisdomUse::AMatrixWisdomUse()
{
    PrimaryActorTick.bCanEverTick = false; // timers only
}

void AMatrixWisdomUse::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Matrix Wisdom Use System Initialized."));

    // Example setup
    AddSkill(TEXT("Programming"), 50.f);
    AddSkill(TEXT("Problem Solving"), 30.f);
    AddSkill(TEXT("Creativity"), 40.f);

    // Automate actions using timers
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(AddSkillTimerHandle, this, &AMatrixWisdomUse::AddRandomSkill, 20.f, true, 5.f);      // every 20s after 5s
        World->GetTimerManager().SetTimer(UpdateSkillTimerHandle, this, &AMatrixWisdomUse::UpdateRandomSkillExperience, 15.f, true, 10.f); // every 15s after 10s
        World->GetTimerManager().SetTimer(CalcWisdomTimerHandle, this, &AMatrixWisdomUse::CalculateAndLogWisdom, 30.f, true, 15.f);       // every 30s after 15s
        World->GetTimerManager().SetTimer(DisplaySkillsTimerHandle, this, &AMatrixWisdomUse::DisplaySkills, 30.f, true, 20.f);            // every 30s after 20s
    }
}

void AMatrixWisdomUse::AddSkill(const FString& SkillName, float InitialExperience)
{
    for (const FLearnedSkill& Skill : SkillDatabase)
    {
        if (Skill.SkillName == SkillName)
        {
            UE_LOG(LogTemp, Warning, TEXT("Skill '%s' already exists."), *SkillName);
            return;
        }
    }

    FLearnedSkill NewSkill(SkillName, InitialExperience);
    SkillDatabase.Add(NewSkill);
    UE_LOG(LogTemp, Log, TEXT("New Skill Added - ID: %s, Name: %s, Experience: %.2f"), *NewSkill.SkillID, *NewSkill.SkillName, NewSkill.ExperienceGained);
}

void AMatrixWisdomUse::UpdateSkillExperience(const FString& SkillName, float AdditionalExperience)
{
    for (FLearnedSkill& Skill : SkillDatabase)
    {
        if (Skill.SkillName == SkillName)
        {
            Skill.AddExperience(AdditionalExperience);
            return;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Skill '%s' not found."), *SkillName);
}

float AMatrixWisdomUse::CalculateWisdom() const
{
    UE_LOG(LogTemp, Log, TEXT("Calculating wisdom from learned skills..."));
    float TotalExperience = 0.f;
    for (const FLearnedSkill& Skill : SkillDatabase)
    {
        UE_LOG(LogTemp, Log, TEXT("Skill '%s', Experience: %.2f"), *Skill.SkillName, Skill.ExperienceGained);
        TotalExperience += Skill.ExperienceGained;
    }

    const int32 Count = SkillDatabase.Num();
    const float Wisdom = Count > 0 ? (TotalExperience / static_cast<float>(Count)) : 0.f;
    UE_LOG(LogTemp, Log, TEXT("Total Experience: %.2f, Calculated Wisdom: %.2f"), TotalExperience, Wisdom);
    return Wisdom;
}

void AMatrixWisdomUse::DisplaySkills() const
{
    UE_LOG(LogTemp, Log, TEXT("Displaying all learned skills..."));
    for (const FLearnedSkill& Skill : SkillDatabase)
    {
        UE_LOG(LogTemp, Log, TEXT("Skill - ID: %s, Name: %s, Experience: %.2f"), *Skill.SkillID, *Skill.SkillName, Skill.ExperienceGained);
    }
}

void AMatrixWisdomUse::AddRandomSkill()
{
    static const TArray<FString> RandomSkills = { TEXT("Leadership"), TEXT("Design"), TEXT("Communication"), TEXT("Critical Thinking") };
    const int32 Index = FMath::RandRange(0, RandomSkills.Num() - 1);
    const FString SkillName = RandomSkills[Index];
    const float Experience = FMath::FRandRange(10.f, 50.f);
    AddSkill(SkillName, Experience);
}

void AMatrixWisdomUse::UpdateRandomSkillExperience()
{
    if (SkillDatabase.Num() > 0)
    {
        const int32 Index = FMath::RandRange(0, SkillDatabase.Num() - 1);
        const float Additional = FMath::FRandRange(5.f, 25.f);
        UpdateSkillExperience(SkillDatabase[Index].SkillName, Additional);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No skills available to update."));
    }
}

void AMatrixWisdomUse::CalculateAndLogWisdom()
{
    const float Wisdom = CalculateWisdom();
    UE_LOG(LogTemp, Log, TEXT("Automated Wisdom Calculation: %.2f"), Wisdom);
}

