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
	

	// Check for Physics Handle Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	// Test to make sure it is all set up properly
	if (PhysicsHandle)
	{
		
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found at %s"), *GetOwner()->GetName());
		InputComponent->BindAction("GrabAction", IE_Pressed, this, &UGrabber::GrabFunction);
	}
	
}

void UGrabber::GrabFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));
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

	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		LineTraceParams 
	);

	// Can see what it hits
	
	AActor* ActorThatWasHit = Hit.GetActor();

	// Prints out to console what object is being hit

	if (ActorThatWasHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace has hit: %s"), *(ActorThatWasHit->GetName()))
	}
}

