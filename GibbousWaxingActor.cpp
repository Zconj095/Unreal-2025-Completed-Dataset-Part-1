#include "GibbousWaxingActor.h"

AGibbousWaxingActor::AGibbousWaxingActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Gibbous Waxing"));
#endif
}

