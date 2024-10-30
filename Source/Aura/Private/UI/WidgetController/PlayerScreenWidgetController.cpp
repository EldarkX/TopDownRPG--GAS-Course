// Copyright Andrii Antropov


#include "UI/WidgetController/PlayerScreenWidgetController.h"

#include "AbilitySystem/AttributeSet/BaseAttributeSet.h"

void UPlayerScreenWidgetController::BroadcastInitialValues()
{
	if (const auto* BaseAttributeSet = WidgetControllerParams.AttributeSet.Get())
	{
		OnHealthChanged.Broadcast(BaseAttributeSet->GetHealth());
		OnMaxHealthChanged.Broadcast(BaseAttributeSet->GetMaxHealth());
		OnManaChanged.Broadcast(BaseAttributeSet->GetMana());
		OnMaxManaChanged.Broadcast(BaseAttributeSet->GetMaxMana());
	}
}

void UPlayerScreenWidgetController::BindDependencies()
{
	const auto* BaseAttributeSet = WidgetControllerParams.AttributeSet.Get();
	UAbilitySystemComponent* ASC = WidgetControllerParams.AbilitySystemComponent.Get();
	
	ASC->GetGameplayAttributeValueChangeDelegate(
		BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthAttributeChanged);
	
	ASC->GetGameplayAttributeValueChangeDelegate(
		BaseAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &ThisClass::OnMaxHealthAttributeChanged);
	
	ASC->GetGameplayAttributeValueChangeDelegate(
		BaseAttributeSet->GetManaAttribute()).AddUObject(this, &ThisClass::OnManaAttributeChanged);
	
	ASC->GetGameplayAttributeValueChangeDelegate(
		BaseAttributeSet->GetMaxManaAttribute()).AddUObject(this, &ThisClass::OnMaxManaAttributeChanged);
}

void UPlayerScreenWidgetController::OnHealthAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UPlayerScreenWidgetController::OnMaxHealthAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UPlayerScreenWidgetController::OnManaAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UPlayerScreenWidgetController::OnMaxManaAttributeChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
