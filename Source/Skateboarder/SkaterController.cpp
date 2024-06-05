// Author: Danilo Brandolin

#include "SkaterController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "SkaterCharacter.h"

void ASkaterController::SetupInput(UEnhancedInputComponent* InComponent)
{
	check(InComponent);
	OwnCharacter = CastChecked<ASkaterCharacter>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
	}

	InComponent->BindAction(MoveAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ASkaterController::Move);
	InComponent->BindAction(LookAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ASkaterController::Look);
	InComponent->BindAction(JumpAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ASkaterController::Jump);
	InComponent->BindAction(SpeedUpAction.LoadSynchronous(), ETriggerEvent::Triggered, this, &ASkaterController::Impulse);

}

void ASkaterController::Move(const FInputActionValue& Value)
{
	OwnCharacter->Move(Value.Get<FVector2D>());

}

void ASkaterController::Look(const FInputActionValue& Value)
{
	OwnCharacter->LookAround(Value.Get<FVector2D>());

}

void ASkaterController::Jump(const FInputActionValue& Value)
{
	OwnCharacter->SkaterJump(Value.Get<float>());
}

void ASkaterController::Impulse(const FInputActionValue& Value)
{
	OwnCharacter->Impulse(Value.Get<float>());
}


