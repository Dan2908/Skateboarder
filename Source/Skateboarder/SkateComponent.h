// Author: Danilo Brandolin
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SKATEBOARDER_API USkateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkateComponent();

	UStaticMesh* GetSkateboardMesh();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
	UPROPERTY(EditAnywhere, Category="Skater Component")
	TSoftObjectPtr<UStaticMesh> SkateboardMesh;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
