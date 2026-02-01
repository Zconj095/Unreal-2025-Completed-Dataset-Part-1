#include "NewMoonActor.h"

ANewMoonActor::ANewMoonActor()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    // Set a readable actor label at construction time (editor only), mirrors prefab name
#if WITH_EDITOR
    SetActorLabel(TEXT("New Moon"));
#endif
}

