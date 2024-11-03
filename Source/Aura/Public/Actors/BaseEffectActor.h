// Copyright Andrii Antropov

#pragma once

#include "GameFramework/Actor.h"
#include "BaseEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API ABaseEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseEffectActor();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "BaseEffectActor")
	void ApplyGameplayEffectToTarget(AActor* EffectTarget, const TSubclassOf<UGameplayEffect>& GameplayEffectClass);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category = "BaseEffectActor")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category = "BaseEffectActor")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;
};
