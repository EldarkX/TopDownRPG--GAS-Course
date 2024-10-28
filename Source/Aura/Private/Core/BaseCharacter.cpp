// Copyright Andrii Antropov

#include "Core/BaseCharacter.h"

#include "AbilitySystem/Components/BaseAbilitySystemComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeapongMesh"));
	WeaponMesh->SetupAttachment(GetMesh(), TEXT("WeaponHandSocket"));
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}
