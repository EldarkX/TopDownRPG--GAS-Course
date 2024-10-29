// Copyright Andrii Antropov


#include "UI/WidgetController/WidgetController.h"

void UWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams)
{
	WidgetControllerParams.PlayerController = InWidgetControllerParams.PlayerController;
	WidgetControllerParams.PlayerState = InWidgetControllerParams.PlayerState;
	WidgetControllerParams.AbilitySystemComponent = InWidgetControllerParams.AbilitySystemComponent;
	WidgetControllerParams.AttributeSet = InWidgetControllerParams.AttributeSet;
}
