#include "SpringActor.h"

ASpringActor::ASpringActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

#if WITH_EDITOR
    SetActorLabel(TEXT("Spring"));
#endif
}

