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

	FindPhysicsHandle();

	SetupInputComponent();
	
}

void UGrabber::FindPhysicsHandle()
{
	// Checking for Physics Handle Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	
	// Making sure Physics Handle is setup properly
	if (PhysicsHandle)
	{
		// Physics Handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle component found on %s"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("GrabAction", IE_Pressed, this, &UGrabber::GrabFunction);
		InputComponent->BindAction("GrabAction", IE_Released, this, &UGrabber::ReleaseFunction);
	}
}

void UGrabber::GrabFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));

	// TODO, to only raycase when key is pressed

	// Try and reach any actors with physics body collision channel set

	// If we hit something then attach the physics handle
	// TODO attach physics handle
}

void UGrabber::ReleaseFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physic handle is attached
		// Move the object we are holding

	GetFirstPhysicsBodyInReach();

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation
	);

	// Draws a line from player outwards displaying Reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

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

	return Hit;
}

