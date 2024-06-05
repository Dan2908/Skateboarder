// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkaterCharacter.generated.h"

class UCameraComponent;
class UCapsuleComponent;
class UEnhancedInputComponent;
class USkateComponent;
class USpringArmComponent;

UCLASS()
class SKATEBOARDER_API ASkaterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkaterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USkateComponent* SkateboardComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SkateboardMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skater Input|Settings")
	float RegularSpeed = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skater Input|Settings")
	float ImpulseSpeed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skater Input|Settings")
	float ImpulseCoolingTime = 3.0f;

public:	

	UFUNCTION(BlueprintCallable)
	const float GetCurrentSpeedNorm();

	// When Impulsing, it turns to 1.0 and goes down to 0 if no new impulses provided
	UFUNCTION(BlueprintCallable)
	const float GetImpulseNorm();

	// 0 to 1, indicating jumping 
	UFUNCTION(BlueprintCallable)
	const float GetJumpNorm();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetSkateboard();

	void Move(const FVector2D Value);
	void LookAround(const FVector2D Value);
	void SkaterJump(float Value);
	void Impulse(const float Value);

	UEnhancedInputComponent* InComponent;

	bool bOnboard = false;

private:

	template<class T>
	inline const T ApplyDelta(const T Value);

	// Auxiliar value to keep track of the impulse cooling
	float ImpulseTime = 0.0f;
};

template<class T>
inline const T ASkaterCharacter::ApplyDelta(const T Value)
{
	return Value * GetWorld()->GetDeltaSeconds();
}


