#include "CrescentWaningActor.h"

ACrescentWaningActor::ACrescentWaningActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Crescent Waning"));
#endif
}

