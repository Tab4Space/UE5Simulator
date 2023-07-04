#include "RimeArrow.h"

#include "FABaseCharacter.h"

ARimeArrow::ARimeArrow()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARimeArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARimeArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARimeArrow::OnBeginDamage(ETraceType TraceType, FVector Modifier)
{
	SkillTargetLocation = FAOwnerCharacter->GetActorLocation();
	Super::OnBeginDamage(TraceType, Modifier);

}

