#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;
class AWeapon;
class ASoul;

UCLASS()
class UE5_RPG_COURSE_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	/* AActor */
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

	/* IHitInterface */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

protected:
	/* AActor */
	virtual void BeginPlay() override;

	/* ABaseCharacter */
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void Die_Implementation() override;

	virtual void AttackEnd() override;
	/**/

	void SpawnSoul();

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

private:
	/* Components */
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASoul> SoulClass;

	/* Navigation */
	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrollingSpeed = 140.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float TargetAcceptanceRadius = 70.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	double PatrolRadius = 200.f;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	FTimerHandle PatrolTimer;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 8.f;

	/* Combat */
	UPROPERTY(EditAnywhere, Category = Combat)
	double CombatRadius = 800.f;
	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRadius = 150.f;

	FTimerHandle AttackTimer;
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;
	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;

	/* AI Behavior */
	void InitializeEnemy();
	void SpawnDefaultWeapon();
	bool InTargetRange(AActor* Target, double Radius);
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	void StartPatrolling();
	void ChaseTarget();
	void LoseInterest();
	bool IsPatrolling();
	bool IsChasing();
	bool IsAttacking();
	bool IsEngaged();
	bool IsDead();
	void StartAttackTimer();
	void PatrolTimerFinished();
	void ClearPatrolTimer();
	void ClearAttackTimer();
	void ShowHealthBar();
	void HideHealthBar();

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn); //Callback for OnPawnSeen in UPawnSensing Component
};
