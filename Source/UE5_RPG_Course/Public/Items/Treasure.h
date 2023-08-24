#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Treasure.generated.h"

UCLASS()
class UE5_RPG_COURSE_API ATreasure : public AItem
{
	GENERATED_BODY()
	
public:
	ATreasure();

	/* AActor */
	virtual void Tick(float DeltaTime) override;

protected:
	/* AItem */
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	/* Properties */
	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Gold;

public:
	FORCEINLINE int32 GetGold() const { return Gold; }
};
