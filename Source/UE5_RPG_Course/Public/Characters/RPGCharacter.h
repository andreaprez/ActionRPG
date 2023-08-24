#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "Interfaces/PickUpInterface.h"
#include "RPGCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class UCustomOverlay;
class ASoul;

UCLASS()
class UE5_RPG_COURSE_API ARPGCharacter : public ABaseCharacter, public IPickUpInterface
{
	GENERATED_BODY()

public:
	ARPGCharacter();

	/* AActor */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void Jump() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	/* IHitInterface */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

	/* IPickUpInterface*/
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGold(ATreasure* Treasure) override;

protected:
	/* AActor */
	virtual void BeginPlay() override;

	/* Input */
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* EKeyAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* AttackAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* DodgeAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EKeyPressed();

	/* ABaseCharacter */
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void Dodge() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void Die_Implementation() override;

	virtual void AttackEnd() override;
	virtual void DodgeEnd() override;
	/**/

	void EquipWeapon(AWeapon* Weapon);
	void Arm();
	void Disarm();
	bool CanArm();
	bool CanDisarm();
	bool IsUnocuppied();
	bool HasEnoughStamina();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();
	UFUNCTION(BlueprintCallable)
	void FinishEquipping();
	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

	void PlayEquipMontage(const FName& SectionName);

private:
	/* Components */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;
	/**/

	/* Animation Montages */
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;
	/**/

	UPROPERTY()
	UCustomOverlay* Overlay;

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	EActionState ActionState = EActionState::EAS_Unoccupied;

	void InitializeInput();
	void InitializeOverlay();

	void SetHUDHealth();
	void SetHUDStamina();
	void SetHUDGold();
	void SetHUDSouls();

public:
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
