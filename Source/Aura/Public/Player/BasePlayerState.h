// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "BasePlayerState.generated.h"

class UBaseAbilitySystemComponent;
class UBaseAttributeSet;

UCLASS()
class AURA_API ABasePlayerState : public APlayerState, public IAbilitySystemInterface
{
private:
	GENERATED_BODY()

public:
	ABasePlayerState();

	FORCEINLINE UBaseAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UPROPERTY()
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;
};
