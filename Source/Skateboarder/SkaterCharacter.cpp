// Fill out your copyright notice in the Description page of Project Settings.

#include "SkaterCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SkateComponent.h"
#include "SkaterController.h"

// Sets default values
ASkaterCharacter::ASkaterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkateboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Skate Mesh"));
	SkateboardMesh->SetupAttachment(RootComponent);

	SkateboardComponent = CreateDefaultSubobject<USkateComponent>(FName("Skateboard Component"));
	AddOwnedComponent(SkateboardComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void ASkaterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

const float ASkaterCharacter::GetCurrentSpeedNorm()
{
	return GetVelocity().Length() / GetMovementComponent()->GetMaxSpeed();
}

const float ASkaterCharacter::GetImpulseNorm()
{
	return std::min(ImpulseTime, 1.0f);
}

const float ASkaterCharacter::GetJumpNorm()
{
	if (JumpKeyHoldTime > 0.0f)
	{
		return 1 / JumpKeyHoldTime;
	}

	return 0.0f;
}

// Called every frame
void ASkaterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ImpulseTime = std::max(0.0f, ImpulseTime - DeltaTime);
}

// ------------- Input -------------

// Called to bind functionality to input
void ASkaterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (ASkaterController* SkaterController = CastChecked<ASkaterController>(Controller))
	{
		SkaterController->SetupInput(InComponent);
	}

}

void ASkaterCharacter::SetSkateboard()
{
	if (SkateboardMesh)
	{
		SkateboardMesh->SetStaticMesh(SkateboardComponent->GetSkateboardMesh());
	}
}

void ASkaterCharacter::Move(const FVector2D Value)
{	
	const FVector2D DeltaValue = ApplyDelta(Value);

	AddMovementInput(GetActorRightVector(), DeltaValue.X);
	AddMovementInput(GetActorForwardVector(), DeltaValue.Y * RegularSpeed);
}

void ASkaterCharacter::LookAround(const FVector2D Value)
{
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);

}

void ASkaterCharacter::SkaterJump(const float Value)
{
	// Avoid jumping when nearly idle
	if (GetCurrentSpeedNorm() < 0.5f)
	{
		return;
	}

	Super::Jump();
}

void ASkaterCharacter::Impulse(const float Value)
{
	// If cooling time isn't over, leave.
	if (ImpulseTime > 0.1f)
	{
		return;
	}
	// if max impulse speed reached, leave
	if (GetMovementComponent()->IsExceedingMaxSpeed(GetMovementComponent()->GetMaxSpeed()))
	{
		return;
	}
	
	AddMovementInput(GetActorForwardVector(), ApplyDelta(ImpulseSpeed));
	ImpulseTime = ImpulseCoolingTime;
}


