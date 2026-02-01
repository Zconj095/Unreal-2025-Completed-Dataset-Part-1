#include "MoonPhasesActor.h"

#include "Components/ChildActorComponent.h"
#include "NewMoonActor.h"
#include "FullMoonActor.h"
#include "HalfMoonActor.h"
#include "GibbousMoonActor.h"
#include "CrescentMoonActor.h"

AMoonPhasesActor::AMoonPhasesActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    NewMoon = CreateDefaultSubobject<UChildActorComponent>(TEXT("NewMoon"));
    NewMoon->SetupAttachment(Root);
    NewMoon->SetChildActorClass(ANewMoonActor::StaticClass());

    FullMoon = CreateDefaultSubobject<UChildActorComponent>(TEXT("FullMoon"));
    FullMoon->SetupAttachment(Root);
    FullMoon->SetChildActorClass(AFullMoonActor::StaticClass());

    HalfMoon = CreateDefaultSubobject<UChildActorComponent>(TEXT("HalfMoon"));
    HalfMoon->SetupAttachment(Root);
    HalfMoon->SetChildActorClass(AHalfMoonActor::StaticClass());

    GibbousMoon = CreateDefaultSubobject<UChildActorComponent>(TEXT("GibbousMoon"));
    GibbousMoon->SetupAttachment(Root);
    GibbousMoon->SetChildActorClass(AGibbousMoonActor::StaticClass());

    CrescentMoon = CreateDefaultSubobject<UChildActorComponent>(TEXT("CrescentMoon"));
    CrescentMoon->SetupAttachment(Root);
    CrescentMoon->SetChildActorClass(ACrescentMoonActor::StaticClass());

#if WITH_EDITOR
    SetActorLabel(TEXT("Moon Phases"));
#endif
}

