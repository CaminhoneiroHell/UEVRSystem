// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h" 	

UCLASS()
class ARCHWALK_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void UpdateDestinationMarker();
	
	//Axis Input Handling
	void MoveForward(float throttle);
	void MoveRight(float throttle);
	
	//Action Input Handling
	void BeginTeleport();
	void FinishTeleport();

private:
		UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

		UPROPERTY(VisibleAnywhere)
		class USceneComponent* VRRoot;

		UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* DestinationMarker;

		UPROPERTY(VisibleAnywhere)
		float MaxTeleportDistance = 1000; //10 meters

		UPROPERTY(VisibleAnywhere)
		float TeleportFadeTime = 1; //In seconds
};
