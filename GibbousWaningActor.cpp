#include "GibbousWaningActor.h"

AGibbousWaningActor::AGibbousWaningActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Gibbous Waning"));
#endif
}

