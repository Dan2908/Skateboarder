// Author: Danilo Brandolin

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "SkaterPawn.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class UEnhancedInputComponent;
class USkateComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UStaticMeshComponent;

UCLASS()
class SKATEBOARDER_API ASkaterPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASkaterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkaterMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SkateboardMesh;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere)
	USkateComponent* Skate;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UEnhancedInputComponent* InComponent;

	bool bOnboard = false;

private:


};
