// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "ABCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);

UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EControlMode : uint8
	{
		GTA = 0,
		DIABLO,
		NPC
	};

	void SetControlMode(EControlMode NewControlMode);
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector;

	float ArmLengthTo = 0.0f;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void PossessedBy(AController* NewController) override;

	bool CanSetWeapon() { return (nullptr == CurrentWeapon); }
	void SetWeapon(class AABWeapon* NewWeapon);

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AABWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UABCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputMappingContext* DefaultMappingContext;

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

//Attack
private:
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, meta = (AllowPrivateAccess = true))
	float AttackRadius;

	UPROPERTY()
	class UABAnimInstance* ABAnim;

//Input Methods
private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ViewChange();

//Input Actions
private:
	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* ViewChangeAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* AttackAction;

private:
	void OnAssetLoadCompleted();

	FSoftObjectPath CharacterAssetToLoad = FSoftObjectPath(nullptr);
	TSharedPtr<struct FStreamableHandle> AssetStreamingHandle;
};
