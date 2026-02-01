#include "OSSSkillTrainerActor.h"

AOSSSkillTrainerActor::AOSSSkillTrainerActor()
{
    PrimaryActorTick.bCanEverTick = false;
    OSS = CreateDefaultSubobject<UOSSSkillComponent>(TEXT("OSSSkillComponent"));
}

void AOSSSkillTrainerActor::BeginPlay()
{
    Super::BeginPlay();

    if (!OSS) { return; }
    OSS->LearnSwordSkillCreation();

    // Build a simple 3-move attack skill
    FOSSSkillDefinition Skill;
    Skill.SkillName = TEXT("Crimson-Arc");
    Skill.SkillType = EOSSSkillType::Attack;
    Skill.Cooldown = 2.5f;

    FOSSMove M1; M1.MoveType = EOSSAttackMove::Slash; M1.Duration = 0.25f; M1.PowerScale = 1.0f; M1.Effect.Particle = DemoParticle; M1.Effect.Sound = DemoSound; Skill.Moves.Add(M1);
    FOSSMove M2; M2.MoveType = EOSSAttackMove::Stab;  M2.Duration = 0.30f; M2.PowerScale = 1.2f; M2.Effect.Particle = DemoParticle; Skill.Moves.Add(M2);
    FOSSMove M3; M3.MoveType = EOSSAttackMove::Swing; M3.Duration = 0.35f; M3.PowerScale = 1.5f; M3.Effect.Particle = DemoParticle; Skill.Moves.Add(M3);

    OSS->AddSkill(Skill);
    OSS->AssignHotkey(DemoHotkeySlot, Skill.SkillName);

    // Practice immediately in safe area
    OSS->SetInSafeArea(true);
    OSS->UseSkillByHotkey(DemoHotkeySlot, /*bPractice=*/true);
}

