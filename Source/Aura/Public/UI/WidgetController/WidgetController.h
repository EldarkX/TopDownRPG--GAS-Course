// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class ABasePlayerState;
class ABasePlayerController;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(
		ABasePlayerController* InPlayerController,
		ABasePlayerState* InPlayerState,
		UAbilitySystemComponent* InAbilitySystemComponent,
		UAttributeSet* InAttributeSet) :
	PlayerController(InPlayerController),
	PlayerState(InPlayerState),
	AbilitySystemComponent(InAbilitySystemComponent),
	AttributeSet(InAttributeSet) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetController")
	TObjectPtr<ABasePlayerController> PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetController")
	TObjectPtr<ABasePlayerState> PlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};

UCLASS()
class AURA_API UWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "WidgetController")
	void SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	FWidgetControllerParams WidgetControllerParams;
};
