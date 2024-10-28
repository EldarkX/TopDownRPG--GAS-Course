// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class IMouseHighlightInterface;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UCLASS()
class AURA_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController();

	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	/*Input*/
	void Move(const FInputActionValue& InputActionValue);

	/*Cursor*/
	void CursorTrace();

private:
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true), Category="BasePlayerController|Input")
	TObjectPtr<UInputMappingContext> BaseInputContext;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true), Category="BasePlayerController|Input")
	TObjectPtr<UInputAction> MoveAction;

	TScriptInterface<IMouseHighlightInterface> LastHighlightedActor;
	TScriptInterface<IMouseHighlightInterface> CurrentHighlightedActor;
};
