// Copyright Andrii Antropov

#include "Actors/BaseEffectActor.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/AttributeSet/BaseAttributeSet.h"
#include "Components/SphereComponent.h"

ABaseEffectActor::ABaseEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());
}

void ABaseEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndOverlap);
}

void ABaseEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a gameplay effect. For now, using  const_cast as a hack...
	if (IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();
		check(AbilitySystemComponent);
		if (const UBaseAttributeSet* BaseAttributeSet =
			Cast<UBaseAttributeSet>(AbilitySystemComponent->GetAttributeSet(UBaseAttributeSet::StaticClass())))
		{
			const_cast<UBaseAttributeSet*>(BaseAttributeSet)->SetHealth(BaseAttributeSet->GetHealth() + 25.f);
			const_cast<UBaseAttributeSet*>(BaseAttributeSet)->SetMana(BaseAttributeSet->GetMana() - 25.f);
		}
		Destroy();
	}
}

void ABaseEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
