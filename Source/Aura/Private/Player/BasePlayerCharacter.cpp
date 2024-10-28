// Copyright Andrii Antropov


#include "Player/BasePlayerCharacter.h"

#include "AbilitySystem/AttributeSet/BaseAttributeSet.h"
#include "AbilitySystem/Components/BaseAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/BasePlayerState.h"

ABasePlayerCharacter::ABasePlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void ABasePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	/* Init ability actor info for the Server */
	InitAbilityActorInfo();
}

void ABasePlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	/* Init ability actor info for the Client */
	InitAbilityActorInfo();
}

void ABasePlayerCharacter::InitAbilityActorInfo()
{
	ABasePlayerState* BasePlayerState = GetPlayerState<ABasePlayerState>();
	check(BasePlayerState);
	BasePlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BasePlayerState, this);
	AbilitySystemComponent = CastChecked<UBaseAbilitySystemComponent>(BasePlayerState->GetAbilitySystemComponent());
	AttributeSet = BasePlayerState->GetAttributeSet();
}
