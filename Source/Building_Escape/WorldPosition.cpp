#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
	
	// FString Log = TEXT("Hello!");
	// FString* PrtLog = &Log; // The address of where it is stored in memory

	// Log.Len();
	// PrtLog->Len();

	// UE_LOG(LogTemp, Warning, TEXT("This is a Warning!"));

	FString ObjectName = GetOwner()->GetName();

	UE_LOG(LogTemp, Warning, TEXT("ObjectName is : %s"), *ObjectName);

}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ... Anything here will be run with every frame of the game
}

