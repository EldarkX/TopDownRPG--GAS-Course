// Copyright Andrii Antropov


#include "AI/BaseAICharacter.h"

#include "AbilitySystem/AttributeSet/BaseAttributeSet.h"
#include "AbilitySystem/Components/BaseAbilitySystemComponent.h"
#include "Aura/Aura.h"

ABaseAICharacter::ABaseAICharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("AttributeSet"));
}

void ABaseAICharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ABaseAICharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetWeaponMesh()->SetRenderCustomDepth(true);
	GetWeaponMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ABaseAICharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	GetWeaponMesh()->SetRenderCustomDepth(false);
}
