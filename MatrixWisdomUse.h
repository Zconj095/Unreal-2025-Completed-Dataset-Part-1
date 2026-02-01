#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MatrixWisdomUse.generated.h"

UCLASS(Blueprintable)
class PEKBGGAP_API AMatrixWisdomUse : public AActor
{
    GENERATED_BODY()

public:
    AMatrixWisdomUse();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Matrix Wisdom")
    void AddSkill(const FString& SkillName, float InitialExperience);

    UFUNCTION(BlueprintCallable, Category = "Matrix Wisdom")
    void UpdateSkillExperience(const FString& SkillName, float AdditionalExperience);

    UFUNCTION(BlueprintCallable, Category = "Matrix Wisdom")
    float CalculateWisdom() const;

    UFUNCTION(BlueprintCallable, Category = "Matrix Wisdom")
    void DisplaySkills() const;

private:
    struct FLearnedSkill
    {
        FString SkillID;
        FString SkillName;
        float ExperienceGained = 0.f;

        FLearnedSkill() = default;
        FLearnedSkill(const FString& InName, float InExp)
            : SkillID(FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens))
            , SkillName(InName)
            , ExperienceGained(InExp)
        {}

        void AddExperience(float AdditionalExperience)
        {
            ExperienceGained += AdditionalExperience;
            UE_LOG(LogTemp, Log, TEXT("Skill '%s' gained %.2f experience. Total: %.2f"), *SkillName, AdditionalExperience, ExperienceGained);
        }
    };

    // Helpers for automation
    UFUNCTION()
    void AddRandomSkill();

    UFUNCTION()
    void UpdateRandomSkillExperience();

    UFUNCTION()
    void CalculateAndLogWisdom();

    // Data store
    TArray<FLearnedSkill> SkillDatabase;

    // Timers (InvokeRepeating equivalents)
    FTimerHandle AddSkillTimerHandle;
    FTimerHandle UpdateSkillTimerHandle;
    FTimerHandle CalcWisdomTimerHandle;
    FTimerHandle DisplaySkillsTimerHandle;
};

