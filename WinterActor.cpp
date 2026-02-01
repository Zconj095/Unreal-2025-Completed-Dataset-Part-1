#include "WinterActor.h"

AWinterActor::AWinterActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Winter"));
#endif
}

