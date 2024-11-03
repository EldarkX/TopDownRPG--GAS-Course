// Copyright Andrii Antropov

#include "Actors/BaseEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot")));
}

void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseEffectActor::ApplyGameplayEffectToTarget(AActor* EffectTarget,
	const TSubclassOf<UGameplayEffect>& GameplayEffectClass)
{
	check(GameplayEffectClass); // it has to be set
	
	if (UAbilitySystemComponent* EffectTargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(EffectTarget))
	{
		FGameplayEffectContextHandle EffectContextHandle = EffectTargetASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle& GameplayEffectSpecHandle = EffectTargetASC->MakeOutgoingSpec(GameplayEffectClass,
			1.f, EffectContextHandle);
		EffectTargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data);
	}
}
