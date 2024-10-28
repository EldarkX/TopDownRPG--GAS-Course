// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseCharacter.h"
#include "Core/Interfaces/MouseHighlightInterface.h"
#include "BaseAICharacter.generated.h"

UCLASS()
class AURA_API ABaseAICharacter : public ABaseCharacter, public IMouseHighlightInterface
{
	GENERATED_BODY()

public:
	ABaseAICharacter();

	virtual void PossessedBy(AController* NewController) override;
	
public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
