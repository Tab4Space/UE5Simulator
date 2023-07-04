#include "Doomsday.h"

ADoomsday::ADoomsday()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADoomsday::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoomsday::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

