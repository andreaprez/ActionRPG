#include "HUD/CustomHUD.h"
#include "HUD/CustomOverlay.h"

void ACustomHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World) 
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && OverlayClass)
		{
			Overlay = CreateWidget<UCustomOverlay>(Controller, OverlayClass);
			Overlay->AddToViewport();
		}
	}
}
