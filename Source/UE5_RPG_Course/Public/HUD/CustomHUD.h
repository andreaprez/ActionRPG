#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CustomHUD.generated.h"

class UCustomOverlay;

UCLASS()
class UE5_RPG_COURSE_API ACustomHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCustomOverlay> OverlayClass;

	UPROPERTY()
	UCustomOverlay* Overlay;

public:
	FORCEINLINE UCustomOverlay* GetOverlay() const { return Overlay; }
};
