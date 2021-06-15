// Daniel Padron 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

private:

	float ClosedAngle;
	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float OpenAngle = -90.f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* DoorTrigger;

	UPROPERTY(EditAnywhere)
	AActor* OpeningActor;

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
	float CloseDoorDelay = 1.f;

	UPROPERTY(EditAnywhere)
	float DoorOpenSpeed;

	UPROPERTY(EditAnywhere)
	float DoorCloseSpeed;

};
