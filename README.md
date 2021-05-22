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
// header:
private:
    //UPROPERTY(VisibleAnywhere)
    class UCameraComponent* Camera;

//class:
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

//header:
private:

	void MoveForward(float throttle);
	void MoveRight(float throttle);

//class:
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



### Proposed solution to attach character on camera 
<br/><br/>

* There's a restriction basically with characters you cant move their capsules.

* Character must move acording the VR head, but because of the childing the player will move together.


	* To solve this: Move the VR root to opposite direction, so it will center character and Camera on desired location.
<br/><br/>

	```c++
	
	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	VRRoot->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);	//Camera attach VR root

	```
<!-- #region Image link -->
![Image](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMMAAAA+CAYAAACWc69tAAATZElEQVR4nO2daVATWbvHg8uMisgizriMo46O+yggWwzpSIQAsoigRkRURFEUFJFN2ZUtIeyCEgggW1ijIMNlriOojEhcYISAIHKXurdqbr116771Lt//9wMQEyAhApLg9IdflZ2Tfs7T3efHOd0V+6EQBIHZgEbQ4Mx2hpuXG05cOIH04nSkFKTAy88LLsdc4ODuACvCSuH+Q0NDYLPZEIvF8PT0BEEQqKmpQUREBB4+fIi4uDhcuXIFv//+O0JCQhASEgI+n4+mpiY4OjpiYGAAwcHBYDKZcHBwgIODA9hsNoaGhqR9eHp6YmBgYFzfhw8fxvv37+U+e/36NS5dujQuhpeXF969eweCIJTGV5Tr8D4fpPvY29tjaGgIzs7OIAgCIpEI8fHxSmMEBARALBZLY3h7e0MikUi39+/fj6GhIbi6us7KtZ8rUCb7AmOGOtpL7IWblxusHayx32k/wpLCEJ0WDccjjqDZ0GDvZg8aQZtUhrS0NOTm5sLR0RHd3d2wtbWVyhAXF4eenh7U19dLEQgEIAgC58+fR2NjI7q7uyEQCMBiscYN1rHbsgNcdjApk8HDwwODg4MTxpPdVpTr2H2UyaAoRlRUFJqamhTKQBAEBgcHwWaz1T4ANYlJZVAFBmPy71DpVBzzOQYrWytYMCxwg3sDHD4H+532w3KfJTzOeYBKp04qw6FDh9DZ2YmEhAQUFxeDIAipDIGBgWhvbx+374EDB+Dh4SH9d0NDA3JyclSW4eDBg/jw4QMYDMaMyaAo10+RQVGMa9eu4dmzZ9LtsTKwWCwMDQ3B3t5e7QNQk5gRGVSBSqfC/aQ7zAlzMB2ZyBHmgJvPBdORCQuGBY56H1VJBoIYHvx9fX3w8fGRbsfFxcHOzg5v375FWFgYrK2t4enpCR8fH5w6dQo9PT1gs9lgMpmorq7+JBmsra3x/v17uWXFdGVQlOtkMlRUVCAvLw/W1tYKYzg5OaG/vx8BAQGwtbVFQUGBnAxsNhu9vb1qH3yaxqzKcC7oHKh0Kg56HET87XjEZcbB/aQ7qHQqfK/5wszKVCUZQkND8fz5c2nbqAwEQeDMmTNoaWlBX18fWlpa4efnB4IgkJCQgNevX6O3txe1tbUT3jMokoEghv8ih4WFzZgMY3NtbR3OdTIZ/Pz80N3dDT6frzAGQRAIDg7Gq1ev8ObNGyQmJqKnp0caMzY2FmVlZWoffLOFKiuXWZVhL7EXx32Pg0qnwpntjPPB53Hmyhkc8jyE3ea7ccjzEHaa7IQZ3UztJ28irl27hvr6erXnMRM0NzdLpVEbMktOTWHWZLAirGBqZYo9e/fAjG6GCyEX4BPoAytbK6z+fjU2bd+EVWtXYafJTtAJutpPzFgYDAaam5tx8eJFtecyHQIDA3H//n2156GJTC6DilPMZNAJOowtjbFp+ybsNt+N88Hn4Rfqh5/2/IQ169Zgw5YNWP/jephQTdR+UhTh4uKC8vJytecxHYRCIRwdHdWehyYyazMDnaDDyMIIu8x2wYRqAiMLIxhbGmPzzs0woZpgt/lubN21VaOWSaquNdWWnwbk8CUxazKQkHwOGDMYi5SBhGQEUoY/CQwNyEHTIWUgIRmBIhbxMBs0liaisCgZd0rScKc8C3dK0yEo5qK+NGlW+ichmYwZkaFDSduLuhQI+Ldwu+I2citzcbf6LvJq8pBXk4e71XeRW5mLfEESnlYmq/1kfC5+KY5Tew7ToZBzWe05zAaffWbI4IXibvVd5AhzwK/jo6y5DDWtNahqqUJJU8mwGLV5SMuMQnstV+0nZKbJjvGFpdEWlb9flR0KCoUyrT4fl8Vj4cIF+JfCmCnHECQHYOmSRRCLeNix+XvcvOqp9nP5uZlxGWQvZHVeJDLuZSC7PBt5NXkQPhKiuasZvw3+hrb3bWh604Sy5jLcqbqDu9V3ce9O9IQxrUy347gLQ+6z9houli1dgqxoX2m/CxfMx1cLF0BvmTYcGHvQUhYvl5ey9qly86onBMkBE7Y9KrmFlYZ6aOBHQiziYYWBLjKiziqNNxMyfEqOipCVofp2GHR1lqB57Ax3X/0DWBU6VMxzRmWgUChyF5LHC0NmSSayyrJQWF+Iho4GdPxHB3r/2ovev/bixb+/wIPnD5AvykeOMAcZeYlor00ZF/fWVU+sNNRDR93HzzKjz0FfdylejMwmFAoFVdmh0kFoYbQZx5wIudyUtU8V2p5tuHrm4IRt/l6OOOxAk27Phgyy50iVHBUhK4NYxIMtzQj+Xo6zOohnmxmTYVQE2QsZnxoBbj4XWaVZKGooQuPLRrz671cY+McABv4xgFf/9QoPxQ8heCBAdnk20gtT0VyaMC72U2ESFn/9FQqTP65dXWzMceQATa7/0cEuFvFw/cJhGG//QeX24pRAbNu0FkuXLIKl0RY0FkRN2kY32w4tLS3Mnz8PTkyzcXlvWrcK2TG+0u1RGaqyQ2Ggp4MQXzcs1V6MNSuXIy/+IsSijzKEnDsEHe3FWPPtxzaxiIdi7hVs2bAGS7UXw9bKCK0ViajKDsVS7cU4coCGtasM8WvpLVAoFDQVxkyY40QxxCIe0iN8sObb5TA0WAYXG3M5GeKDTmDTulVqH7AaL4OsCLIyRHPCkZCTgNTCVPDr+Kh7Voen/U/R+UcnOv/oxNP+p6h7Voe8mjzwBDzE347Hw+KbE/ZhRzfG8YPDS6X2Gi50dZagIClALgdhZgjaa7ho4EfCfNeP8HAmVGp/KkyCgZ4OogOO4VllEo67MGA0IoqyNrFI8V/dp8IkUCgUPJZZisnKoKVFQcTFo2irSsY5NgtbN34nJ0OUPxttVck4y2Zh84bVEIt4aK1IxHI9HSSHnkJbZTIYFjtxls2S7pMcchJiEU9OhrE5KorRWpEI7cWLEHvZA60ViXC33ysnQwM/ElpaFDyv5szIwFP20GXOyjBWBFkZQqMvIyYtBgk5CUgvTkdxYzEePH+A5q5mNHc14/5v96VLpJKmEhQ1FOFfa9Mn7Cc9wgcrV+hDLOIhK9oXq77RV5rHxu9X4qkwSaX2lOveWLvKUPrd1vIEaGlpoYEfqbRNmQx1ueFYMH++3GeyMsiep5LUq1j09UI5GUbbytKvYeHCBcN5hntDb5k24oNOID7oBA470GCyY+O4fZTJoChGWoSP3Dkdu0xqq0wGhUKRHveXyLRkmEgE2YtyI/wcwhLDEJESgZtZN5FSkILcylwIHgggeCBAVmkWihuL8fYvb/H+n++H+ds7/PrrPXTUyd87tNdwobdMG4WcyzhoY4FTbsxxuYSdd0fqjTOI8mdjuZ4OLp44oFJ7qK8bTH/aJBdv2dLhmUdZmzIZSlKvyg0mZTJUZARj3rx5E8oguz26dLI02iLlEIv6STIoinHd74jcsnGsDGIRD/PmzZNban5pTFkGRSLIXeTsMFy6fgmhCaG4wb2BmPQYJOYmgifggZvPBYfPQdcfXR9FkEEkTB3Xp7v9Xhx3YUBXZwkqMoLH5SN7oQJOOsFs148qtadc98a61Sukba0VidDS0kL9yMygqE2ZDI0FUdDS0sILGamnKwM37LTcLDXRdyaTQVGMxGAvbPx+pUIZWssTQKFQ8GvpLbUPWo2TQVVCr5xAUFwQQuJDEMWLAofPQVZpFjh8DngCHvr/1j+hDF3/2T4uFj/hEpYs/nrCGzmKlvxgj7x0FD9tWadQBtn2JxWJ0NdditjLHmirTIbnwX3YvXX9pG1iEQ+2VkY46mg1bi3dXsPFgvnz8TD/4434dGVoKYuHrs4SxAUeR3sNF2VpQeAnXJpUBtkcFcVoLorF118tRFqED55McM9QlR2KJYu/VvuAndMytFYk4sypg/C/4Y+Y9Bhkl2dD8ECA2IxYhCWGKZwZBv5PMi5WRx0PK1foyy1/FA32O7f8oKuzBE9GnpRM1l7IuYwtP6yB9uJFMN+9WW5trKwtO8YXy5YukXuEOgptzzbEXvGYMRnEIh4KkgKw5Yc1WLzoK2zesBrZMb4fv3N/YhnG5jhRDLGIh4RrXvjWUA+GBstw+ZQzdLQXS/sN9XWDPWGi9gE7p2UYFeJGwDH4nDuCG/HBSOFzcD74PA4dP4iGjgZ0/U8X+v8uP0M86/pZ7SdnuiQGe8HCaLPa85gJdm/bIPeY+Etk1n6oN0pLeQIa8qNw+bQzbK2McCXkHH4b/A2df3Ti7V/eoud/e9D+b+2ozo9V+8mZLh11POzeuh6Z0efUnst04Iadxl6TrWrP43Mz6zKM8qQiESnXveF/0gnXgrxR8iAfFU3FKK3KRsMX9EvWxoJo2NGN1Z7HdLClGc35HxuqgtpkGOVnQTRqboehLjf8T3HCSTQXtctAQqIpkDKQkIxAykBCMgIpAwnJCBrzQgAaQQONoMkVLKERNFjSLZUWMZlrMDQghy+JmXzRm0bIQCNoOHnxJC6FX4Iz2xnmdHNQ6VSY0c3AzefCkm6p9hxng4+vfdS8l/KqwunTp9Wew3TQCBnM6ebgCXjIq81DSVMJCusL4XjEERYMCzR0NIBgDb/FW915fk78/Pw+6S3fyl6fryp2dnYYGBiAk5PTlGPIFkJ59OgRQkND1X4up4pGyGDtYI2MexlIKUhBVlkWSppKUPesDtx8LhpfNqLoYRHM6eYqX+CSkhJIJBJ0dXWhrKxsyhebMUvH7+DggJcvX0qLoYzWflC2z0zIMJbQ0FB4e3t/0j6yMhw9ehRv376dsy821ggZjvseR2ZJJlKLUsET8JBenI7yX8pR01qD8l/K8fOrn2F9wFqlewehUAiRSARHR0epGA0NDbN6PIxPrD2QnJwsLT5CELMjw0Q5ypbIUpWxJbKEQiGSk5PVPqamgkbIwOFzkHEvA6lFqUgrSkNqYSpiM2KRXpyOKF4Urt28BmsH63FLJTpBlxPE1dUVg4OD0io3BEHAyckJEokETCYTBDG8HGlra0NfXx8ePnwIFxcX6eDq6uoCh8OBRCJBe3s7PD09UVZWhr6+PohEIrBYLBAEgZMnT6KlpQU9PT2oqKiQFkvs6ekBn8+X1llT1NdYnjx5Ilc8RLYqUFdXF2JjY9HT04MXL17g7NmzcjKMFjns6OiQtqmao2xVoLq6Onz48AGDg4PSWnkTxSAIAv7+/ujo6MCbN29QVFQkJ0NISAiePHmi9jE1Z2WgWlORUpCCzJJMpBWlIb04HRw+B7mVuej/ez/KfylHdFo0LPdZwpJuCXO6OczoZthnvw92h+ykcfz8/PDy5UuF/TAYDIjFYly8eBFMJhOVlZUoLCyUG1zh4eGwsbFBbW0tJBIJ/P39wWKx0Nrailu3boHFYqGzsxNXr17F/v37UVNTg7S0NOn+QUFBk/Ql/xfZxsYGQ0NDsLP7eBxjS2RFRkaCyWQiNTUVjx8/lss3IiICTCYTaWlpaG1tBUEQE+aYnj4+R2XFExUdJ4vFgkQiQXh4OFgsFvLz8+VkcHV1xdDQEKytrdU+ruakDHuJvTChmiAsKQxZZVnILMkEh89B/O143K2+i9ontSisL0RRQxEuhFxASkEKqlqqkJyXjDOXz0jjBAYGytV6UyaFg4MDEhISpCVixy47wsPD8eLFC+l2dnY2ioqKJqnfPH7ZMlFfssx+jWnVKon+GWtMa4QMBDH8eNXE0gT2bvbIKstCbEYsNu/cDO/L3jh79SwevX2E5x+eg8PnIK82DyG3QqCrpwsq7WOFUFVmhtzcXLx79w4SiQT9/f1obm6ecHAFBQXJlY9NS0uDUChUuX6zsr5kIWtMaw4aIwOdoMPC0gJbd2zF1l1bcerSKXy34Tsk3U0CzYYG9hk2Mu5lIL04HbcrbsPwW0Ps+GmHXIzRewbZp0dOTk7o7u4Gk8mEn58fJBKJ9EJFRkZ+sgyq1m9W1pcsZI1pzUEjZDA1NcXy5cthYGCA1WtW47t132Hj1o1IL07Hzayb+Gb1N9DR10FmSSZyhDlw83KDvoE+6HQ66HT5YohCoRC1tbXSp0nFxcUQiUQgiOEbv66uLjg6OsLV1RXNzc2fLIOq9ZuV9SULWWNac9AIGSwtLaGvrw89PT3o6elBX18f+sv18cOWH7DDeAe+Wf0N3LzckFuZC56AB+2l2li/fj127doFU1P52tF2dnYoLS1Fb28vurq6cO/ePTg4OEgHXlVVFfr6+vD48WNkZWWhra3tk2QgCNXqNyvrayxkjWnNQCNkIAgCVlZWMDU1xcqVK2FoaPhRDAN9rFq7Cn6hfsitzIWNsw10dHSk7QYGBmrPfbqQNaY1A42RYSzm5uYwNjbG2rVrsXb9WkTyIsET8KBvKD+DWFnN/R/xja0xzdCAnKbCXK8xrbEyjEKn07F953bYOtuCuo8KXV1d6OnpYcWKFdi2bZva85spyBrT6md2ZZjiz23NzM1gbmkOYxNjbNu2DVQqdWbzIiEh5sDMQEIyW5AykEydGfyPNZoAKQMJyQikDCQkI5AykJCMQPH19QUJCYkvOTOQkIxCyqCEmXwNCYnmQ8pAQjICKQMJyQikDCQkI0xLBne2O3h5PLiz3RV+x+vsSTwbeIawm+FqP1gSEmVMWYZREQpqCpQKwbnDxft/vkdefbHaD5bk8zGXf61KEMOvxvx//yRYczsAq28AAAAASUVORK5CYII=)

<!-- #endregion -->
___

## Line tracing a teleportation 
<br/><br/>
 1. Find the teleport destination
 2. Show the destination to the player
 3. Fade out the viewport
 4. Move the player to the destination 
 5. Fade back in

<br/><br/>

```c++
//In Editor create an primitive object attached on player (Use blueprints to it, apparently is required go very deep in UE classes hyerarch to create primitives in c++)


//header:
private:

	void UpdateDestinationMarker();

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* DestinationMarker;

	UPROPERTY(VisibleAnywhere)
	float MaxTeleportDistance = 1000; //10 meters

//class:
//Calls on AVRCharacter attaching the destination marker position to Root Component (The BP_VRCharacter) :
	DestinationMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestinationMarker"));
	DestinationMarker->SetupAttachment(GetRootComponent());

void AVRCharacter::UpdateDestinationMarker()
{
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * MaxTeleportDistance;

	FHitResult HitResult;
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	if (bHit) {
		DestinationMarker->SetWorldLocation(HitResult.Location);
	}
}



// Problem: If there's collision our primitive will be hit by the ray that is being projected to the worod.

// Solution: BP Editor -> DestinationMarker -> Details Panel -> Collision -> Collision Presets -> Set to NoCollision



```




<br/><br/>
## <b> Unity to Unreal glossary </b> 

|Unity | Unreal | API Reference |
|-----|-------| ----- |
|Mesh| UStaticMeshComponent|https://docs.unrealengine.com/en-US/API/Runtime/Engine/Components/UStaticMeshComponent/index.html
|RayCast|UWorld::LineTraceSingleByChannel|https://docs.unrealengine.com/en-US/API/Runtime/Engine/Engine/UWorld/LineTraceSingleByChannel/index.html
 
 ```c++

bool LineTraceSingleByChannel
(
    struct FHitResult & OutHit, // Empty hit result
    const FVector & Start, // Pass a reference toi the memory but cant edit that memory. When we dont put const in memory type parameter we indicate that value mighty be changed
    const FVector & End,
    ECollisionChannel TraceChannel,
    const FCollisionQueryParams & Params,	//Optional
    const FCollisionResponseParams & ResponseParam //Optional
) const 

 ```