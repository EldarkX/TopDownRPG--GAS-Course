// Copyright Andrii Antropov

#pragma once

#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "BaseEffectActor.generated.h"

class UGameplayEffect;
struct FGameplayEffectSpecHandle;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	OnBeginOverlap,
	OnEndOverlap,
	None
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	OnEndOverlap,
	None
};

USTRUCT(BlueprintType)
struct FCustomGameplayEffect
{
	GENERATED_BODY()

	bool IsASCRegistered(UAbilitySystemComponent* ASC) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomGameplayEffect")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomGameplayEffect")
	EEffectApplicationPolicy EffectApplicationPolicy = EEffectApplicationPolicy::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomGameplayEffect")
	EEffectRemovalPolicy EffectRemovalPolicy = EEffectRemovalPolicy::None;

	UPROPERTY()
	TMap<UAbilitySystemComponent*, FActiveGameplayEffectHandle> ActiveGameplayEffectHandles;
};

UCLASS()
class AURA_API ABaseEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseEffectActor();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "BaseEffectActor")
	void OnBeginOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable, Category = "BaseEffectActor")
	void OnEndOverlap(AActor* TargetActor);

private:
	void ApplyGameplayEffectToTarget(AActor* EffectTarget, FCustomGameplayEffect& CustomGameplayEffect);
	void RemoveGameplayEffectFromTarget(UAbilitySystemComponent* TargetASC,
		const FActiveGameplayEffectHandle& CustomGameplayEffectHandle);

	bool IsRemovable(const FGameplayEffectSpecHandle& GameplayEffectSpecHandle,
		const FCustomGameplayEffect& CustomGameplayEffect) const;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category = "BaseEffectActor")
	TArray<FCustomGameplayEffect> CustomGameplayEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category = "BaseEffectActor")
	float ActorLevel = 1.f;
};
