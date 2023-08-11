// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class LAWLESS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/** Components */
	UPROPERTY(EditanyWhere, BlueprintReadWrite, Category = FPBoomStick)
		class USpringArmComponent* FPSpringArmComponent;

	UPROPERTY(EditanyWhere, BlueprintReadWrite, Category = FPCamera)
		class UCameraComponent* FPCameraComponent;
	
	// Movement Functions
	void Idle(bool NotMoving);
	// Manages the timer idle
	FORCEINLINE void IdleManager(){ IdleTracker--;};
	
	void MoveForward(float value);
	void MoveSide(float Value);
	void Sprint();
	void Crouch();

	void CheckMovementBooleans(bool CheckWalk, bool CheckRun, bool CheckCrouch);

	// Movement Variables
	float DefaultSpeed = 500.f;

	bool bIsWalking = false;
	bool bIsSprinting = false;
	bool bIsCrouching = false;
	
	// Action Functions
	void Interact();


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Head Bob for Idle animation
	FTimerHandle IdleBob;
	int32 IdleTracker = 0;
	
};
