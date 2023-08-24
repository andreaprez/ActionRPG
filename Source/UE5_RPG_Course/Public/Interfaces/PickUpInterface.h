#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickUpInterface.generated.h"

class AItem;
class ATreasure;
class ASoul;

UINTERFACE(MinimalAPI)
class UPickUpInterface : public UInterface
{
	GENERATED_BODY()
};

class UE5_RPG_COURSE_API IPickUpInterface
{
	GENERATED_BODY()

public:
	virtual void SetOverlappingItem(AItem* Item);
	virtual void AddGold(ATreasure* Treasure);
	virtual void AddSouls(ASoul* Soul);
};