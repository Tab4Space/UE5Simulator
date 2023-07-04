#pragma once

#include "CoreMinimal.h"
#include "FABaseSkill.h"
#include "RimeArrow.generated.h"

UCLASS()
class FINDARK_API ARimeArrow : public AFABaseSkill
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARimeArrow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnBeginDamage(ETraceType TraceType, FVector Modifier) override;
};
