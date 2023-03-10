// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealEngineTraining/AnimationSystem/Public/Character/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "UnrealEngineTraining/AnimationSystem/Public/Character/MyCharacterMovementComponent.h"

FName APlayerCharacter::NAME_IgnoreOnlyPawn(TEXT("IgnoreOnlyPawn"));
const bool bNinjaMovement = false;

// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UMyCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// CapsuleHasRoomCheck(GetCapsuleComponent(),
	// 	GetCapsuleComponent()->GetComponentLocation()
	// 	,0,2,EDrawDebugTrace::ForOneFrame,true);
}

void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

FVector APlayerCharacter::GetCapsuleBaseLocation(UCapsuleComponent* Capsule, float ZOffset)
{
	return Capsule->GetComponentLocation() -
		Capsule->GetUpVector() * (Capsule->GetScaledCapsuleHalfHeight() + ZOffset);
}

FVector APlayerCharacter::GetCapsuleLocationFromBase(UCapsuleComponent* Capsule, FVector BaseLocation, float ZOffset)
{
	BaseLocation.Z += Capsule->GetScaledCapsuleHalfHeight() + ZOffset;
	return BaseLocation;
}

bool APlayerCharacter::CapsuleHasRoomCheck(UCapsuleComponent* Capsule, FVector TargetLocation, float HeightOffset,
	float RadiusOffset, EDrawDebugTrace::Type DebugType, bool DrawDebugTrace)
{
	//??????????????????TargetLocation?????????
	const float ZOffset = Capsule->GetScaledCapsuleHalfHeight_WithoutHemisphere() + HeightOffset - RadiusOffset;
	FVector TraceStart = TargetLocation;
	TraceStart.Z += ZOffset;
	FVector TraceEnd = TargetLocation;
	TraceEnd.Z -= ZOffset;
	const float Radius = Capsule->GetUnscaledCapsuleRadius() + RadiusOffset;

	const UWorld* World = Capsule->GetWorld();
	check(World);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Capsule->GetOwner());
	
	const bool bHit = World->SweepSingleByChannel(HitResult, TraceStart, TraceStart, FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(Radius), Params);

	//TODO ZYF	??????Debug?????????
	if (DrawDebugTrace)
	{
		UKismetSystemLibrary::SphereTraceSingle(
			World,
			TraceStart,
			TraceEnd,
			Radius,
			ETraceTypeQuery::TraceTypeQuery1,
			false,
			TArray<AActor*>(),
			DebugType,
			HitResult,
			true,FLinearColor::Green, FLinearColor::Red);
	}
	

	const bool HasRoom = !(HitResult.bBlockingHit || HitResult.bStartPenetrating);
	if (HasRoom)
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("?????????"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("????????????"));
	}
	return HasRoom;
}

bool APlayerCharacter::MantleCheck(const FMantleTraceSettings& TraceSettings, EDrawDebugTrace::Type DebugType)
{
	ACharacter* OwnerCharacter = this;
	if (!OwnerCharacter)
	{
		return false;
	}

	//const FVector& TraceDirection = OwnerCharacter.HasMo
	
	return true;
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// ??????Controller???????????????????????????????????????
		const FRotator Rotation = Controller->GetControlRotation();

		//Yaw??????Z???????????????????????????????????????????????????????????????????????????
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		
		// get forward vector
		//X????????????
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		if (bNinjaMovement)
		{
			//????????????????????????????????????
			AddMovementInput(FVector::ForwardVector, Value);
		}
		else
		{
			//????????????????????????????????????????????????
			AddMovementInput(Direction, Value);
		}
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		
		if (bNinjaMovement)
		{
			AddMovementInput(FVector::RightVector, Value);
		}
		else
		{
			AddMovementInput(Direction, Value);
		}
	}
}

