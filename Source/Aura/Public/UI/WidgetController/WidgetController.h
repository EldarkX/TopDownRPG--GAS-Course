// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetController.generated.h"

class UBaseAttributeSet;
class UAbilitySystemComponent;
class ABasePlayerState;
class ABasePlayerController;

UCLASS()
class AURA_API UWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<ABasePlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<ABasePlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UBaseAttributeSet> AttributeSet;
};
