#include "SeasonsActor.h"

#include "Components/ChildActorComponent.h"
#include "SpringActor.h"
#include "SummerActor.h"
#include "AutumnActor.h"
#include "WinterActor.h"

ASeasonsActor::ASeasonsActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    Spring = CreateDefaultSubobject<UChildActorComponent>(TEXT("Spring"));
    Spring->SetupAttachment(Root);
    Spring->SetChildActorClass(ASpringActor::StaticClass());

    Summer = CreateDefaultSubobject<UChildActorComponent>(TEXT("Summer"));
    Summer->SetupAttachment(Root);
    Summer->SetChildActorClass(ASummerActor::StaticClass());

    Autumn = CreateDefaultSubobject<UChildActorComponent>(TEXT("Autumn"));
    Autumn->SetupAttachment(Root);
    Autumn->SetChildActorClass(AAutumnActor::StaticClass());

    Winter = CreateDefaultSubobject<UChildActorComponent>(TEXT("Winter"));
    Winter->SetupAttachment(Root);
    Winter->SetChildActorClass(AWinterActor::StaticClass());

#if WITH_EDITOR
    SetActorLabel(TEXT("Seasons"));
#endif
}

