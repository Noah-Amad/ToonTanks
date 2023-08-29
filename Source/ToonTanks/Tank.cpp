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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		/*DrawDebugSphere(
			GetWorld(),
			HitResult.ImpactPoint,
			20.f,
			12,
			FColor::Red,
			false,
			-1.f);*/
		RotateTurret(HitResult.ImpactPoint);
	}

}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
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

