## UE + VR Ramp-up

#### Setting Up basic scene:

---
* In Blank Scene notes:
    
    * PlayerController.AbsoluteRotation: Has VR rotation update.
    * PlayerController.location: does not update    
    
    * PlayerCameraManager.Rotation: VR Update 
    * PlayerCameraManager.location: update acording move input

---

# Creating VRCharacter

## Set Camera
```c++
header:
s
private:
		//UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

file:

#include "Camera/CameraComponent.h"

// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
}
```

```blueprint

    Blueprints > GameMode: GameModeBase > Create > GameModeBase

    Change default pawn class to my character class

```

## Set movement
<p> </p>

```c++ 

header:
private:

	void MoveForward(float throttle);
	void MoveRight(float throttle);

file:
// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &AVRCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AVRCharacter::MoveRight);
}

void AVRCharacter::MoveForward(float throttle)
{
	AddMovementInput(throttle * Camera->GetForwardVector());
}

void AVRCharacter::MoveRight(float throttle)
{
	AddMovementInput(throttle * Camera->GetRightVector());
}
```

* Create axis mapping on UE interface.

```bash
    settings -> Project settings -> Engine/Input -> Create axis mapping*
```
___
