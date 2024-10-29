// Copyright Andrii Antropov

#pragma once

#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

struct FWidgetControllerParams;
class UBaseUserWidget;
class UPlayerScreenWidgetController;

UCLASS()
class AURA_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void InitPlayerScreen(const FWidgetControllerParams& InWidgetControllerParams);
	
	UPlayerScreenWidgetController* GetPlayerScreenWidgetController() { return PlayerScreenWidgetController; }
	
private:
	UPROPERTY()
	TObjectPtr<UBaseUserWidget> PlayerScreenWidget;

	UPROPERTY()
	TObjectPtr<UPlayerScreenWidgetController> PlayerScreenWidgetController;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBaseUserWidget> PlayerScreenWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerScreenWidgetController> PlayerScreenWidgetControllerClass;

};
