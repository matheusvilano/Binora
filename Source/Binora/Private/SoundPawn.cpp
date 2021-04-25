// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "SoundPawn.h"

#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#pragma region Initialization

	// Sets default values
	ASoundPawn::ASoundPawn()
	{
		#pragma region Framework
		{
			// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
			this->AActor::PrimaryActorTick.bCanEverTick = false;

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
		// Set the Sphere Radius. Note: values are clamped. Min=0, Max=1000.
		this->ADefaultPawn::GetCollisionComponent()->InitSphereRadius(this->SphereRadius);

		// Force this Pawn to be at Z = 0.0f
		{
			// Get current location; adjust Z to 0.
			FVector Location = this->AActor::GetActorLocation();
			Location.Z = 0;

			// Force SoundPawn to Z = 0.
			this->AActor::SetActorLocation(Location);
		}
	}

	// Called to bind functionality to input
	void ASoundPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
	{
		// Setup
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		// Set Volume binding for any SoundType
		PlayerInputComponent->BindAxis("Volume", this, &ADefaultPawn::MoveForward);

		// Set Panning binding for non-Background SoundPawnTypes
		if (this->SoundType != ESoundActorType::ST_Background1 && this->SoundType != ESoundActorType::ST_Background2)
		{
			PlayerInputComponent->BindAxis("Panning", this, &ADefaultPawn::MoveRight);
		}
	}

	// Called when the game starts or when spawned
	void ASoundPawn::BeginPlay()
	{
		// Parent's BeginPlay
		Super::BeginPlay();
	}

#pragma endregion

#pragma region Possession

	// Runs every time the pawn gets possessed.
	void ASoundPawn::PossessedBy(AController * NewController)
	{
		if (this->InputEnabled())
		{
			this->FMODAudioComponent->Play();
		}
	}

	// Runs every time the player gets unposssessed.
	void ASoundPawn::UnPossessed()
	{
		if (this->InputEnabled())
		{
			this->FMODAudioComponent->Stop();
		}
	}

#pragma endregion