#include "CrescentWaxingActor.h"

ACrescentWaxingActor::ACrescentWaxingActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Crescent Waxing"));
#endif
}

