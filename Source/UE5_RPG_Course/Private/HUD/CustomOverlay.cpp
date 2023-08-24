#include "HUD/CustomOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UCustomOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UCustomOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void UCustomOverlay::SetGold(int32 Gold)
{
	if (GoldText)
	{
		const FString GoldString = FString::FromInt(Gold);
		GoldText->SetText(FText::FromString(GoldString));
	}
}

void UCustomOverlay::SetSouls(int32 Souls)
{
	if (SoulsText)
	{
		const FString SoulsString = FString::FromInt(Souls);
		SoulsText->SetText(FText::FromString(SoulsString));
	}
}
