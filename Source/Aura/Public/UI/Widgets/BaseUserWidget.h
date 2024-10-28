// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseUserWidget.generated.h"

UCLASS()
class AURA_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
	
public:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
};
