#include "FullMoonActor.h"

AFullMoonActor::AFullMoonActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Full Moon"));
#endif
}

