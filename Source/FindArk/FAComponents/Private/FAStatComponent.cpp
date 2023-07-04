// Fill out your copyright notice in the Description page of Project Settings.


#include "FAStatComponent.h"
#include "FAGameInstance.h"
#include "FABaseCharacter.h"
#include "Kismet/GameplayStatics.h"


UFAStatComponent::UFAStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	MaxHealth = 1000.f;
	MaxMana = 100.f;
	BaseAttackDamage = 100.f;
	BaseArmor = 10.f;
	CriticalProb = 1.f;
}


void UFAStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFAStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UFAStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFAStatComponent::InitStatData()
{
	UFAGameInstance*	FAGameInstance = Cast<UFAGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	AFABaseCharacter*	Character = Cast<AFABaseCharacter>(GetOwner());

	MaxHealth			= FAGameInstance->GetSettingData().Characters[Character->PlayerId].MaxHealth;
	MaxMana				= FAGameInstance->GetSettingData().Characters[Character->PlayerId].MaxMana;
	BaseAttackDamage	= FAGameInstance->GetSettingData().Characters[Character->PlayerId].BaseAttackDamage;
	BaseArmor			= FAGameInstance->GetSettingData().Characters[Character->PlayerId].BaseArmor;
	CriticalProb		= FAGameInstance->GetSettingData().Characters[Character->PlayerId].CriticalProb;
}
