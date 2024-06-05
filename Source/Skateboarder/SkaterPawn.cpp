// Author: Danilo Brandolin

#include "SkaterPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SkateComponent.h"
#include "SkaterController.h"

// Sets default values
ASkaterPawn::ASkaterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(FName("Capsule"));
	RootComponent = Capsule;

	SkaterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Skater Mesh"));
	SkaterMesh->SetupAttachment(RootComponent);

	// Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	// Skate
	Skate = CreateDefaultSubobject<USkateComponent>(FName("Skate Component"));
	AddOwnedComponent(Skate);

	SkateboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Skate Mesh"));
	SkateboardMesh->SetupAttachment(RootComponent);
	SkateboardMesh->SetStaticMesh(Skate->GetSkateboardMesh());

}

// Called when the game starts or when spawned
void ASkaterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkaterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkaterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	InComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (ASkaterController* SkaterController = CastChecked<ASkaterController>(Controller))
	{
		SkaterController->SetupInput(InComponent);
	}

}

