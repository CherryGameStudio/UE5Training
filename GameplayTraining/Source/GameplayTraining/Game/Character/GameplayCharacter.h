// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameplayCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPlayerMappableInputConfig;
class UGameplayInputActionConfig;

UCLASS()
class GAMEPLAYTRAINING_API AGameplayCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGameplayCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly)
	UPlayerMappableInputConfig* PMIConfig;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UGameplayInputActionConfig> InputActionConfig;

	UFUNCTION()
	void InputMove(const FInputActionValue& Value);

	UFUNCTION()
	void InputLook(const FInputActionValue& Value);
};
