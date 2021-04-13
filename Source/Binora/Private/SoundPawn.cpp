// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "SoundPawn.h"


#pragma region Constructors

	// Sets default values
	ASoundPawn::ASoundPawn()
	{
		#pragma region Framework
		{
			// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
			this->AActor::PrimaryActorTick.bCanEverTick = true;
		}
		#pragma endregion

		#pragma region Gameplay
		{
			this->SphereComp = this->UObject::CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
			this->AActor::SetRootComponent(this->SphereComp);
			this->SphereComp->SetSphereRadius(100.0f, 100.0f, 100.0f); // Starting point for radius.
		}
		#pragma endregion

		#pragma region Sound
		{
			this->FMODAudioComp = this->UObject::CreateDefaultSubobject<UFMODAudioComponent(TEXT("Sound"));
		}
		#pragma endregion
	}

#pragma endregion

// Called every frame
void ASoundPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASoundPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
