// Copyright Andrii Antropov


#include "UI/Widgets/BaseUserWidget.h"

void UBaseUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
