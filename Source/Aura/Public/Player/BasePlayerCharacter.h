// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseCharacter.h"
#include "BasePlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURA_API ABasePlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABasePlayerCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }
	FORCEINLINE UCameraComponent* GetCameraComponent() const { return CameraComponent; }

private:
	void InitAbilityActorInfo();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="BasePlayerCharacter")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="BasePlayerCharacter")
	TObjectPtr<UCameraComponent> CameraComponent;
};
