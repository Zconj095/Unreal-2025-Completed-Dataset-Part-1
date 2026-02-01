#include "HalfMoonActor.h"

AHalfMoonActor::AHalfMoonActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Half Moon"));
#endif
}

