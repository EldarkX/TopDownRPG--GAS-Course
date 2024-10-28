// Copyright Andrii Antropov

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MouseHighlightInterface.generated.h"

UINTERFACE(MinimalAPI)
class UMouseHighlightInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API IMouseHighlightInterface
{
	GENERATED_BODY()

public:
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
