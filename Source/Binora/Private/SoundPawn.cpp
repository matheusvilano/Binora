// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "SoundPawn.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#pragma region Constructors

	// Sets default values
	ASoundPawn::ASoundPawn()
	{
		#pragma region Framework
		{
			// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
			this->AActor::PrimaryActorTick.bCanEverTick = true;

			// Deactivate Default Movement Bindings
			this->ADefaultPawn::bAddDefaultMovementBindings = false;
		}
		#pragma endregion

		#pragma region Gameplay
		{
			// Sphere
			USphereComponent* SphereComp = this->ADefaultPawn::GetCollisionComponent();
			SphereComp->SetGenerateOverlapEvents(true); // For counting the score.
		}
		#pragma endregion

		#pragma region Sound
		{
			this->FMODAudioComponent = this->UObject::CreateDefaultSubobject<UFMODAudioComponent>(TEXT("FMOD Audio Component"));
			this->FMODAudioComponent->USceneComponent::SetupAttachment(this->AActor::GetRootComponent());
			this->FMODAudioComponent->USceneComponent::SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
			this->FMODAudioComponent->bAutoActivate = false;
		}
		#pragma endregion
	}

	// Construction script
	void ASoundPawn::OnConstruction(const FTransform& Transform)
	{
		// Set the FMOD Event. Note: there is no null check here; make sure you assign the reference in the Details panel.
		this->FMODAudioComponent->SetEvent(this->FMODEvent);

		// Set the Mesh Material. Note: will not be visible in-game. Use for visual reference at design time.
		if (this->MeshColour) // if not a nullptr
		{
			this->ADefaultPawn::GetMeshComponent()->SetMaterial(0, this->MeshColour);
		}

		// Set the Sphere Radius. Note: values are clamped. Min=0, Max=1000.
		this->ADefaultPawn::GetCollisionComponent()->InitSphereRadius(this->SphereRadius);
	}

#pragma endregion

#pragma region Framework

	// Called to bind functionality to input
	void ASoundPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
	{
		// Setup
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		// Set Volume binding for any SoundPawnType
		PlayerInputComponent->BindAxis("Volume", this, &ADefaultPawn::MoveForward);

		// Set Panning binding for non-Background SoundPawnTypes
		if (this->SoundPawnType != ESoundPawnType::SPT_Background1 && this->SoundPawnType != ESoundPawnType::SPT_Background2)
		{
			PlayerInputComponent->BindAxis("Panning", this, &ADefaultPawn::MoveRight);
		}
	}

#pragma endregion