// Daniel Padron 2021

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Grabber is active"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	// Prints in output log the location and rotation values for our PlayerView
	// UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"),
	// 	*PlayerViewPointLocation.ToString(),
	// 	*PlayerViewPointRotation.ToString()
	// );

	// Draws a line from player outwards displaying Reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 0, 255),
		false,
		0.f,
		0,
		5
	);

	// Need to use Ray-cast to a certain distance (Reach)
	FHitResult Hit;

	FCollisionQueryParams LineTraceParams(FName(TEXT("")), false, GetOwner());



	// Can see what it hits


}

