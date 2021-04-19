// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "SoundActor.h"

#pragma region Constructors

	// Sets default values
	ASoundActor::ASoundActor()
	{
		#pragma region Inherited
		{
			// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
			this->AActor::PrimaryActorTick.bCanEverTick = true;
		}
		#pragma endregion

		#pragma region Sound
		{
			this->FMODAudioComponent = this->UObject::CreateDefaultSubobject<UFMODAudioComponent>(TEXT("FMOD Audio Component"));
			this->SetRootComponent(this->FMODAudioComponent); // Set as root component
			this->FMODAudioComponent->bAutoActivate = false; // Prevent the component from automatically playing sound
		}
		#pragma endregion

		#pragma region Score
		{
			// Inner Sphere
			{
				this->InnerSphereComponent = this->UObject::CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere Component"));
				this->InnerSphereComponent->USceneComponent::SetupAttachment(this->AActor::GetRootComponent());
				this->InnerSphereComponent->UPrimitiveComponent::SetGenerateOverlapEvents(true); // For counting the score.
				this->InnerSphereComponent->USphereComponent::InitSphereRadius(this->InnerSphereRadius); // Default radius
			}
			// Middle Sphere
			{
				this->MiddleSphereComponent = this->UObject::CreateDefaultSubobject<USphereComponent>(TEXT("Middle Sphere Component"));
				this->MiddleSphereComponent->USceneComponent::SetupAttachment(this->AActor::GetRootComponent());
				this->MiddleSphereComponent->UPrimitiveComponent::SetGenerateOverlapEvents(true); // For counting the score.
				this->MiddleSphereComponent->USphereComponent::InitSphereRadius(this->MiddleSphereRadius); // Default radius
			}
			// Outer Sphere
			{
				this->OuterSphereComponent = this->UObject::CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere Component"));
				this->OuterSphereComponent->USceneComponent::SetupAttachment(this->AActor::GetRootComponent());
				this->OuterSphereComponent->UPrimitiveComponent::SetGenerateOverlapEvents(true); // For counting the score.
				this->OuterSphereComponent->USphereComponent::InitSphereRadius(this->OuterSphereRadius); // Default radius
			}
		}
		#pragma endregion
	}

	// Construction script
	void ASoundActor::OnConstruction(const FTransform& Transform)
	{
		// Force Z axis to 0 and NO rotation
		{
			FVector Location = this->AActor::GetActorLocation();
			this->AActor::SetActorLocation(FVector(Location.X, Location.Y, 0.0f));
			this->AActor::SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		}

		// Set the FMOD Event. Note: there is no null check here; make sure you assign the reference in the Details panel.
		this->FMODAudioComponent->SetEvent(this->FMODEvent);

		// Set the sphere outline colour. Note: will not be visible in-game. Use for visual reference at design time.
		this->InnerSphereComponent->ShapeColor = SphereColour;
		this->MiddleSphereComponent->ShapeColor = SphereColour;
		this->OuterSphereComponent->ShapeColor = SphereColour;

		// Set the Sphere Radius. Note: values are clamped.
		this->InnerSphereComponent->InitSphereRadius(this->InnerSphereRadius);
		this->MiddleSphereComponent->InitSphereRadius(this->MiddleSphereRadius);
		this->OuterSphereComponent->InitSphereRadius(this->OuterSphereRadius);
	}

#pragma endregion

#pragma region Inherited

	// Called when the game starts or when spawned
	void ASoundActor::BeginPlay()
	{
		// Parent's BeginPlay
		Super::BeginPlay();

		// Play sound as soon as the Actor lives
		this->FMODAudioComponent->Play();
	}

#pragma endregion