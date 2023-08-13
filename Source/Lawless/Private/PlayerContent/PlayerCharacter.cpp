// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerContent/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Lawless/Public/WeaponContent/Base_RangedWeapon.h"

FString& printf(const wchar_t* Str, const FString& String);
// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("FPSpringArmComponent"));
	FPSpringArmComponent->SetupAttachment(RootComponent);

	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPCameraComponent"));
	FPCameraComponent->SetupAttachment(FPSpringArmComponent, USpringArmComponent::SocketName);
	FPCameraComponent->SetFieldOfView(60.f);


	FPSpringArmComponent->TargetArmLength = 0.f;
	
	// Gets the current location of the object  
	//FVector SpringArmPreLoc = FPSpringArmComponent->GetComponentLocation();
	
	FVector SpringLoc (20.f, 0.f, 80.f);
	FPSpringArmComponent->SetWorldLocation(SpringLoc);
	
	IdleTracker = 2;
	
}

void APlayerCharacter::Idle(bool NotMoving)
{
	// Sets the Spring's Locations
	FVector SpringLoc (20.f, 0.f, 80.f);
	FVector SpringLoc_New (20.f, 0.f, 65.f);
	
	// For the first the function is called.
	
	
	if (IdleTracker > 1)
	{
		return;
	} else {
		
		if(IdleTracker != 0)
		{
			GetWorld()->GetTimerManager().SetTimer(IdleBob, this, &APlayerCharacter::IdleManager, 1, true);
			FPSpringArmComponent->SetWorldLocation(SpringLoc_New);
		
		} else {

		}
	}
}


void APlayerCharacter::MoveForward(float value)
{
	CheckMovementBooleans(true,NULL,NULL);
	
	if (value != 0)
	{
		AddMovementInput(GetActorForwardVector(), value);
		if(bIsSprinting)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sprinting"));
			AddMovementInput(GetActorForwardVector(), value + 500.f);
		} else {return;}
	}
}

void APlayerCharacter::MoveSide(float value)
{
	if(value != 0)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void APlayerCharacter::Sprint()
	{
	// Call check movement, ignore other booleans as they are not relevant. Set the Sprinting boolean to true.  
	CheckMovementBooleans(NULL, true, NULL);
	UE_LOG(LogTemp, Warning, TEXT("Sprint Function"));
}

void APlayerCharacter::Run(float Value)
{
	
	AddMovementInput(GetActorForwardVector(), Value + 500.f);
	
}

void APlayerCharacter::Crouch() 
{
	
	if(bIsCrouching)
	{
		//capsule height half
	}
}

void APlayerCharacter::CheckMovementBooleans(bool CheckWalk, bool CheckRun, bool CheckCrouch)
{
	
	// Check if all movement is false
	if(!CheckWalk && !CheckRun && !CheckCrouch)
	{
		// check if the character vectors are not moving 
		///*if((MoveForward(0.f)) && (MoveSide(0.f)))
		
		Idle(true);
	}

	if(CheckWalk && CheckRun && !CheckCrouch)
	{
		bIsSprinting = true;
		UE_LOG(LogTemp, Warning, TEXT("Sprint true"));
	}else
	{
		bIsSprinting = false;
		
	}
}

 
void APlayerCharacter::Trace()
{
/** Optimise later maybe try a inline function to only be used for tick idk  **/
	FCollisionQueryParams TraceParams;
	FHitResult FHit;
	
	FVector TraceStart = FPCameraComponent->GetComponentLocation();
	FVector ForwardVector = FPCameraComponent->GetForwardVector();
	FVector TraceEnd((ForwardVector * 400.f) + TraceStart);

	bool bHit = GetWorld()->LineTraceSingleByChannel(FHit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);
	if (bHit)
	{
		DrawDebugSphere(GetWorld(), FHit.ImpactPoint, 5, 1, FColor::Red, false, 0.01, 0, 4);
		if(FHit.bBlockingHit)
		{
			
		}
	} 
}

void APlayerCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Limits Player's Viewport Pitch. 
	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (PlayerController->PlayerCameraManager)
		{
			PlayerController->PlayerCameraManager->ViewPitchMin = -80.0;
			PlayerController->PlayerCameraManager->ViewPitchMax = 70.0;
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check's for specific requirements every Tick.
	CheckMovementBooleans(bIsWalking, bIsSprinting, bIsCrouching);
	Trace();
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement Input
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSide", this, &APlayerCharacter::MoveSide);

	PlayerInputComponent->BindAxis("Run", this, &APlayerCharacter::Run);
	
	
	// Mouse Input
	PlayerInputComponent->BindAxis("Look Down / Look Up", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look RIght / Look Left", this, &APawn::AddControllerYawInput);

	
	
	//Action Input
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::Crouch);

	PlayerInputComponent->BindAction("Interact / Pickup", IE_Pressed, this, &APlayerCharacter::Interact);
	
}

