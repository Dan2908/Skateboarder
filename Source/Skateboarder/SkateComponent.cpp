// Author: Danilo Brandolin

#include "SkateComponent.h"

#include "SkaterCharacter.h"

// Sets default values for this component's properties
USkateComponent::USkateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

UStaticMesh* USkateComponent::GetSkateboardMesh()
{
	return SkateboardMesh.LoadSynchronous();

}


// Called when the game starts
void USkateComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}

void USkateComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
	if (PropertyName == GET_MEMBER_NAME_CHECKED(USkateComponent, SkateboardMesh)) 
	{
		if (ASkaterCharacter* Skater = Cast<ASkaterCharacter>(GetOwner()))
		{
			Skater->SetSkateboard();
		}
	}


}



// Called every frame
void USkateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

