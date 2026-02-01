#include "GibbousMoonActor.h"

#include "Components/ChildActorComponent.h"
#include "GibbousWaxingActor.h"
#include "GibbousWaningActor.h"

AGibbousMoonActor::AGibbousMoonActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    WaxingChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("GibbousWaxing"));
    WaxingChild->SetupAttachment(Root);
    WaxingChild->SetChildActorClass(AGibbousWaxingActor::StaticClass());

    WaningChild = CreateDefaultSubobject<UChildActorComponent>(TEXT("GibbousWaning"));
    WaningChild->SetupAttachment(Root);
    WaningChild->SetChildActorClass(AGibbousWaningActor::StaticClass());

#if WITH_EDITOR
    SetActorLabel(TEXT("Gibbous Moon"));
#endif
}

