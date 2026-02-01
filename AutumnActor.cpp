#include "AutumnActor.h"

AAutumnActor::AAutumnActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Autumn"));
#endif
}

