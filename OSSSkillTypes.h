// Original Sword Skill (OSS) basic types: skill kinds, moves, and effects
#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "OSSSkillTypes.generated.h"

UENUM(BlueprintType)
enum class EOSSSkillType : uint8
{
    Attack  UMETA(DisplayName="Attack"),
    Support UMETA(DisplayName="Support"),
    Utility UMETA(DisplayName="Utility")
};

UENUM(BlueprintType)
enum class EOSSAttackMove : uint8
{
    Slash      UMETA(DisplayName="Slash"),
    Stab       UMETA(DisplayName="Stab"),
    Swing      UMETA(DisplayName="Swing"),
    Projectile UMETA(DisplayName="Projectile")
};

USTRUCT(BlueprintType)
struct PEKBGGAP_API FOSSSpecialEffect
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect")
    UParticleSystem* Particle = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect")
    USoundBase* Sound = nullptr;

    // Optional socket to attach particle to on the owner mesh
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect")
    FName AttachSocket;
};

USTRUCT(BlueprintType)
struct PEKBGGAP_API FOSSMove
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move")
    EOSSAttackMove MoveType = EOSSAttackMove::Slash;

    // Seconds the move lasts (for sequencing/timing)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move", meta=(ClampMin=0.05))
    float Duration = 0.3f;

    // Multiplier fed to gameplay for damage/heal/buff scaling
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move")
    float PowerScale = 1.0f;

    // Optional animation montage section name to play
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move")
    FName MontageSection;

    // Visual/audio FX to fire when this move starts
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move")
    FOSSSpecialEffect Effect;
};

USTRUCT(BlueprintType)
struct PEKBGGAP_API FOSSSkillDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    FName SkillName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    EOSSSkillType SkillType = EOSSSkillType::Attack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    TArray<FOSSMove> Moves;

    // Global cooldown after the full sequence completes
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skill")
    float Cooldown = 2.0f;
};

