// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float Value)
{
	// Adds local movement by adding to its FVector's X value
	AddActorLocalOffset(FVector(Value * TankSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), 0.0f, 0.0f), true);
}

void ATank::Turn(float Value)
{
	// Adds local rotation to our Tank by updating its Yaw
	AddActorLocalRotation(FRotator(0.0f, Value * TankTurnRate * UGameplayStatics::GetWorldDeltaSeconds(this), 0.0f), true);
}

