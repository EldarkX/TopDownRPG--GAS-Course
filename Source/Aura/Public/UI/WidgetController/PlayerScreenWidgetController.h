// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/WidgetController.h"
#include "PlayerScreenWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

struct FOnAttributeChangeData;

UCLASS(BlueprintType, Blueprintable)
class AURA_API UPlayerScreenWidgetController : public UWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindDependencies() override;
	virtual	void BroadcastInitialValues() override;

protected:
	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data) const;
	void OnMaxHealthAttributeChanged(const FOnAttributeChangeData& Data) const;
	void OnManaAttributeChanged(const FOnAttributeChangeData& Data) const;
	void OnMaxManaAttributeChanged(const FOnAttributeChangeData& Data) const;

public:
	UPROPERTY(BlueprintAssignable, Category="Player Screen Widget Controller")
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="Player Screen Widget Controller")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="Player Screen Widget Controller")
	FOnManaChangedSignature OnManaChanged;
	
	UPROPERTY(BlueprintAssignable, Category="Player Screen Widget Controller")
	FOnMaxManaChangedSignature OnMaxManaChanged;
};
