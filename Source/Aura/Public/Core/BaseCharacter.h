// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UBaseAttributeSet;
class UBaseAbilitySystemComponent;

UCLASS(Abstract)
class AURA_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
	FORCEINLINE UBaseAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UBaseAttributeSet> AttributeSet;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="BaseCharacter")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;
};
