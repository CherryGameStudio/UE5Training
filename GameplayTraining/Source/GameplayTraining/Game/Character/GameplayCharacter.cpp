// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameCharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "PlayerMappableInputConfig.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayTraining/Game/Input/GameplayInputConfig.h"


AGameplayCharacter::AGameplayCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UGameCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	// Capsule

	
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->FieldOfView = 90;
	CameraComponent->bConstrainAspectRatio = false;
	CameraComponent->bUsePawnControlRotation = true;	// 使用Controller的视角
	CameraComponent->SetupAttachment(CameraBoom);
	
	// CharacterMovement
	
}

// Called when the game starts or when spawned
void AGameplayCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameplayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGameplayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	check(EnhancedInputComponent);

	APlayerController* PC = GetController<APlayerController>();
	check(PC);

	if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		for(const TTuple<UInputMappingContext*, int> ContextToPriority : PMIConfig->GetMappingContexts())
		{
			InputSystem->AddMappingContext(ContextToPriority.Key, ContextToPriority.Value);
		}
	}

	if (EnhancedInputComponent)
	{
		for (FGameplayInputAction InputAction : InputActionConfig->InputActions)
		{
			for(ETriggerEvent TriggerEvent : InputAction.TriggerEvents)
			{
				EnhancedInputComponent->BindAction(InputAction.InputAction, TriggerEvent, static_cast<UObject*>(this), InputAction.UFunctionName);
			}
		}
	}
}

void AGameplayCharacter::InputMove(const FInputActionValue& Value)
{
	AController* LocalController = GetController();
	if(!LocalController)
		return;

	FVector2D Velocity2D = Value.Get<FVector2D>();
	FRotator MovementRotation = FRotator(0, LocalController->GetControlRotation().Yaw, 0);

	// X为Forward方向
	if (float MoveValue = Velocity2D.X)
	{
		FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector); 
		AddMovementInput(MovementDirection, MoveValue);
	}

	// Y为Right方向
	if (float MoveValue = Velocity2D.Y)
	{
		FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector); 
		AddMovementInput(MovementDirection, MoveValue);
	}
}

void AGameplayCharacter::InputLook(const FInputActionValue& Value)
{
	AController* LocalController = GetController();
	if(!LocalController)
		return;

	// 鼠标X轴正值(右)是Yaw顺时针旋转
	FVector2D Look2D = Value.Get<FVector2D>();
	if (float LookValue = Look2D.X)
	{
		AddControllerYawInput(LookValue);
	}

	// 鼠标Y轴正值(上)是Pitch逆时针旋转
	if (float LookValue = Look2D.Y)
	{
		AddControllerPitchInput(-LookValue);
	}
}

