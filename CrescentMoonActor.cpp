#include "CrescentMoonActor.h"

#include "Components/ChildActorComponent.h"
#include "CrescentWaxingActor.h"
#include "CrescentWaningActor.h"

ACrescentMoonActor::ACrescentMoonActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    WaxingChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("CrescentWaxing"));
    WaxingChild->SetupAttachment(Root);
    WaxingChild->SetChildActorClass(ACrescentWaxingActor::StaticClass());

    WaningChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("CrescentWaning"));
    WaningChild->SetupAttachment(Root);
    WaningChild->SetChildActorClass(ACrescentWaningActor::StaticClass());

#if WITH_EDITOR
    SetActorLabel(TEXT("Crescent Moon"));
#endif
}

