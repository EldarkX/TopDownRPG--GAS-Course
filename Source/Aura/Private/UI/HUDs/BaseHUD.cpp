// Copyright Andrii Antropov

#include "UI/HUDs/BaseHUD.h"

#include "UI/WidgetController/PlayerScreenWidgetController.h"
#include "UI/Widgets/BaseUserWidget.h"

void ABaseHUD::InitPlayerScreen(const FWidgetControllerParams& InWidgetControllerParams)
{
	checkf(PlayerScreenWidgetClass, TEXT("Player screen widget is nullptr, please fill out HUD in BP"));
	checkf(PlayerScreenWidgetControllerClass, TEXT("Player screen widget is nullptr, please fill out HUD in BP"));

	PlayerScreenWidgetController = NewObject<UPlayerScreenWidgetController>(this,
		PlayerScreenWidgetControllerClass);
	PlayerScreenWidgetController->SetWidgetControllerParams(InWidgetControllerParams);
	
	PlayerScreenWidget = CreateWidget<UBaseUserWidget>(GetWorld(), PlayerScreenWidgetClass);
	PlayerScreenWidget->SetWidgetController(PlayerScreenWidgetController);

	PlayerScreenWidgetController->BindDependencies();
	PlayerScreenWidgetController->BroadcastInitialValues();
	
	PlayerScreenWidget->AddToViewport();
}
