#include "Items/Treasure.h"
#include "Interfaces/PickUpInterface.h"
#include "Components/StaticMeshComponent.h"


ATreasure::ATreasure()
{
}

void ATreasure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation = FRotator(0, DeltaTime * 45.f, 0);
	AddActorWorldRotation(Rotation);
}

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickUpInterface* PickUpInterface = Cast<IPickUpInterface>(OtherActor);
	if (PickUpInterface)
	{
		PickUpInterface->AddGold(this);

		SpawnPickupSystem();
		SpawnPickupSound();

		Destroy();
	}
}
