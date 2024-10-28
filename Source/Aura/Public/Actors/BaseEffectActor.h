// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEffectActor.generated.h"

class USphereComponent;

UCLASS()
class AURA_API ABaseEffectActor : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseEffectActor();

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;
};
