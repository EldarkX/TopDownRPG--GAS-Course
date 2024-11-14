// Copyright Andrii Antropov


#include "AbilitySystem/AttributeSet/BaseAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Algo/MaxElement.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UBaseAttributeSet::UBaseAttributeSet()
{
	InitHealth(80.f);
	InitMaxHealth(100.f);
	InitMana(80.f);
	InitMaxMana(100.f);
}

void UBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttributes(Attribute, NewValue);
}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties SourceEffectProperties;
	SetSourceProps(Data, SourceEffectProperties);
	FEffectProperties TargetEffectProperties;
	SetTargetProps(Data, TargetEffectProperties);
}

void UBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Health, OldHealth);
}

void UBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxHealth, OldMaxHealth);
}

void UBaseAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, Mana, OldMana);
}

void UBaseAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBaseAttributeSet, MaxMana, OldMaxMana);
}

void UBaseAttributeSet::ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UBaseAttributeSet::SetSourceProps(const FGameplayEffectModCallbackData& Data, FEffectProperties& SourceProps)
{
	SourceProps.GameplayEffectContextHandle = Data.EffectSpec.GetContext();

	SourceProps.AbilitySystemComponent =
		SourceProps.GameplayEffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (const auto* SourceASC = SourceProps.AbilitySystemComponent)
	{
		SourceProps.AvatarActor = SourceASC->GetAvatarActor();
		SourceProps.Controller = SourceASC->AbilityActorInfo->PlayerController.Get();

		if (auto* Controller = SourceProps.Controller; !Controller)
		{
			if (const APawn* Pawn = Cast<APawn>(SourceProps.AvatarActor))
			{
				SourceProps.Controller = Pawn->GetController();
			}
		}
		if (SourceProps.Controller)
		{
			SourceProps.Character = Cast<ACharacter>(SourceProps.Controller->GetPawn());
		}
	}
}

void UBaseAttributeSet::SetTargetProps(const FGameplayEffectModCallbackData& Data, FEffectProperties& TargetProps)
{
	TargetProps.GameplayEffectContextHandle = Data.EffectSpec.GetContext();

	TargetProps.AvatarActor = Data.Target.GetAvatarActor();
	TargetProps.Controller = Data.Target.AbilityActorInfo->PlayerController.Get();
	TargetProps.Character = Cast<ACharacter>(TargetProps.AvatarActor);
	TargetProps.AbilitySystemComponent =
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetProps.AvatarActor);
}