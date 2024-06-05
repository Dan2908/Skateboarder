// Author: Danilo Brandolin
//
// Note: The enhanced input system is mostly re-used from my "Builder" project.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "SkaterController.generated.h"

class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
class ASkaterCharacter;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class SKATEBOARDER_API ASkaterController : public APlayerController
{
	GENERATED_BODY()

public:

	void SetupInput(UEnhancedInputComponent* InComponent);
	
protected:

	UPROPERTY(EditAnywhere, Category = "Skater Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category = "Skater Input|Actions")
	TSoftObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Skater Input|Actions")
	TSoftObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = "Skater Input|Actions")
	TSoftObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Skater Input|Actions")
	TSoftObjectPtr<UInputAction> SpeedUpAction; // and slow down

private:

	// Hooks
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Impulse(const FInputActionValue& Value);

	ASkaterCharacter* OwnCharacter;

};
