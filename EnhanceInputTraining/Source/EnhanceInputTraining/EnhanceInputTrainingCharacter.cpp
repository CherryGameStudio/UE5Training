// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnhanceInputTrainingCharacter.h"

#include "EnhancedActionKeyMapping.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedPlayerInput.h"
#include "InputMappingContext.h"
#include "PlayerMappableInputConfig.h"

//////////////////////////////////////////////////////////////////////////
// AEnhanceInputTrainingCharacter

AEnhanceInputTrainingCharacter::AEnhanceInputTrainingCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEnhanceInputTrainingCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		for (const auto IMCToPriority : InputConfig->GetMappingContexts())
		{
			UInputMappingContext* IMC = IMCToPriority.Key;
			int Priority = IMCToPriority.Value;
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<APlayerController>(GetController())->GetLocalPlayer()))
			{
				Subsystem->AddMappingContext(IMC, Priority);
			}

			
			if (IMC->GetName() == FString(TEXT("IMC_Char_Move")))
			{
				const TArray<FEnhancedActionKeyMapping>& Mappings = IMC->GetMappings();

				// TSet<const UInputAction*> UniqueActions;
				// for (const FEnhancedActionKeyMapping& Keymapping : Mappings)
				// {
				// 	UniqueActions.Add(Keymapping.Action);
				// }
				//
				// for (const UInputAction* UniqueAction : UniqueActions)
				// {
				// 	EnhancedInputComponent->BindAction(UniqueAction, ETriggerEvent::Triggered, Cast<UObject>(this), UniqueAction->GetFName());
				// }
				
				for (const FEnhancedActionKeyMapping& Mapping : Mappings)
				{
					EnhancedInputComponent->BindAction(Mapping.Action, ETriggerEvent::Triggered,  Cast<UObject>(this), Mapping.PlayerMappableOptions.Name);
					UE_LOG(LogTemp, Warning, TEXT("Mapping.PlayerMappableOptions.Name: %s"), *Mapping.PlayerMappableOptions.Name.ToString())
				}
			}
		}
		
		// const TArray<FEnhancedActionKeyMapping>& Mappings = IMC->GetMappings();
		// for (const FEnhancedActionKeyMapping& Mapping : Mappings)
		// {
		// 	//不用传统的绑定方式
		// 	//EnhancedInputComponent->BindAction(Mapping.Action, ETriggerEvent::Triggered, Cast<UObject>(this), FName("函数名"));
		//
		// 	//所有键盘输入都去监听
		// 	EnhancedInputComponent->BindAction(Mapping.Action, ETriggerEvent::Triggered, this, &ThisClass::InputHandle, Mapping.Action, ETriggerEvent::Triggered);
		// 	EnhancedInputComponent->BindAction(Mapping.Action, ETriggerEvent::Started, this, &ThisClass::InputHandle, Mapping.Action, ETriggerEvent::Started);
		// 	EnhancedInputComponent->BindAction(Mapping.Action, ETriggerEvent::Ongoing, this, &ThisClass::InputHandle, Mapping.Action, ETriggerEvent::Ongoing);
		// 	EnhancedInputComponent->BindAction(Mapping.Action, ETriggerEvent::Canceled, this, &ThisClass::InputHandle, Mapping.Action, ETriggerEvent::Canceled);
		// 	EnhancedInputComponent->BindAction(Mapping.Action, ETriggerEvent::Completed, this, &ThisClass::InputHandle, Mapping.Action, ETriggerEvent::Completed);
		// }
	}
}

void AEnhanceInputTrainingCharacter::InputHandle(const UInputAction* InputAction, ETriggerEvent ListeningEvent)
{
	const FInputActionInstance* InputActionInstance = nullptr;
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<APlayerController>(GetController())->GetLocalPlayer()))
	{
		const UEnhancedPlayerInput* EnhancedPlayerInput = Subsystem->GetPlayerInput();
		InputActionInstance = EnhancedPlayerInput->FindActionInstanceData(InputAction);
	}
	
	if (InputActionInstance)
	{
		auto GetTriggerEventName = [&](ETriggerEvent Event)->FString
		{
			FString TriggerEventName;
			switch (Event)
			{
			case ETriggerEvent::Triggered:
				TriggerEventName = TEXT("Triggered");
				break;
			case ETriggerEvent::Started:
				TriggerEventName = TEXT("Started");
				break;
			case ETriggerEvent::Ongoing:
				TriggerEventName = TEXT("Ongoing");
				break;
			case ETriggerEvent::Canceled:
				TriggerEventName = TEXT("Canceled");
				break;
			case ETriggerEvent::Completed:
				TriggerEventName = TEXT("Completed");
				break;
			default:
				TriggerEventName = TEXT("None");
				break;
			}
			return TriggerEventName;
		};

		FString ListeningTriggerEventName = GetTriggerEventName(ListeningEvent);
		FString CurTriggerEventName = GetTriggerEventName(InputActionInstance->GetTriggerEvent());
		
		UE_LOG(LogTemp, Warning, TEXT("InputHandle Process! ListeningTriggerEvent: %s, CurTriggerEvent: %s, IA Name: %s, InputValue: %s"),
			*ListeningTriggerEventName,
			*CurTriggerEventName,
			*InputAction->GetName(),
			*InputActionInstance->GetValue().ToString()
			)
	}

	switch (InputActionInstance->GetTriggerEvent())
	{
		case ETriggerEvent::Triggered:
			if (InputAction->GetName() == TEXT("IA_Char_Forward"))
			{
				MoveForwardOnTrigger(InputActionInstance->GetValue().GetMagnitude());
			}
			break;
		case ETriggerEvent::Started:
			break;
		case ETriggerEvent::Ongoing:
			break;
		case ETriggerEvent::Canceled:
			break;
		case ETriggerEvent::Completed:
			break;
		default:
			break;
	}
}

void AEnhanceInputTrainingCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AEnhanceInputTrainingCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AEnhanceInputTrainingCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AEnhanceInputTrainingCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AEnhanceInputTrainingCharacter::OnInputMoveForward(const FInputActionValue& InputActionValue)
{
	float Value = InputActionValue.Get<float>();
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEnhanceInputTrainingCharacter::OnInputMoveRight(const FInputActionValue& InputActionValue)
{
	float Value = InputActionValue.Get<float>();
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AEnhanceInputTrainingCharacter::MoveForwardOnTrigger(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEnhanceInputTrainingCharacter::MoveRightOnTrigger(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
