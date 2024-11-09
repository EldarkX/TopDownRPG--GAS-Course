// Copyright Andrii Antropov

#include "Actors/BaseEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

bool FCustomGameplayEffect::IsASCRegistered(UAbilitySystemComponent* ASC) const
{
	return EffectRemovalPolicy == EEffectRemovalPolicy::OnEndOverlap && ActiveGameplayEffectHandles.Contains(ASC);
}

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEffectActor::ApplyGameplayEffectToTarget(AActor* EffectTarget, FCustomGameplayEffect& CustomGameplayEffect)
{
	check(CustomGameplayEffect.GameplayEffectClass); // it has to be set
	
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectTarget))
	{
		FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle& GameplayEffectSpecHandle =
			TargetASC->MakeOutgoingSpec(CustomGameplayEffect.GameplayEffectClass, 1.f, EffectContextHandle);

		const auto& ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data);

		if (IsRemovable(GameplayEffectSpecHandle, CustomGameplayEffect))
		{
			CustomGameplayEffect.ActiveGameplayEffectHandles.Add(TargetASC,	ActiveEffectHandle);
		}
	}
}

void ABaseEffectActor::RemoveGameplayEffectFromTarget(UAbilitySystemComponent* TargetASC,
	const FActiveGameplayEffectHandle& CustomGameplayEffectHandle)
{
	TargetASC->RemoveActiveGameplayEffect(CustomGameplayEffectHandle);
}

bool ABaseEffectActor::IsRemovable(const FGameplayEffectSpecHandle& GameplayEffectSpecHandle,
	const FCustomGameplayEffect& CustomGameplayEffect) const
{
	return GameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite
			&& CustomGameplayEffect.EffectRemovalPolicy != EEffectRemovalPolicy::None;
}

void ABaseEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	for (auto& CustomGameplayEffect : CustomGameplayEffects)
	{
		if (CustomGameplayEffect.EffectApplicationPolicy == EEffectApplicationPolicy::OnBeginOverlap)
		{
			ApplyGameplayEffectToTarget(TargetActor, CustomGameplayEffect);
		}
	}
}

void ABaseEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
	{
		for (auto& CustomGameplayEffect : CustomGameplayEffects)
		{
			if (CustomGameplayEffect.EffectApplicationPolicy == EEffectApplicationPolicy::OnEndOverlap)
			{
				ApplyGameplayEffectToTarget(TargetActor, CustomGameplayEffect);
			}
			if (CustomGameplayEffect.IsASCRegistered(TargetASC))
			{
				RemoveGameplayEffectFromTarget(TargetASC,
					CustomGameplayEffect.ActiveGameplayEffectHandles.FindAndRemoveChecked(TargetASC));
			}
		}
	}
}
