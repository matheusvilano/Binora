// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "FMODAudioComponent.h"
#include "FMODEvent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "SoundActorType.h"
#include "UObject/UObjectGlobals.h"

#include "SoundPawn.generated.h"

// Forward declaration
class UFMODAudioComponent;
class UFMODEvent;
class USphereComponent;
class UMaterialInterface;

UCLASS(DontCollapseCategories=("Sound Pawn"), HideCategories=("Materials", "FMODAudio", "Cooking", "Rendering", "Camera", "Replication", "Input", "Actor", "HLOD"))
class BINORA_API ASoundPawn : public ADefaultPawn
{
	GENERATED_BODY()

	#pragma region Initialization

		public:

			// Sets default values for this pawn's properties.
			ASoundPawn();

			// Construction script
			virtual void OnConstruction(const FTransform& Transform) override;

			// Called to bind functionality to input.
			virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		protected:
			
			// Called when the game starts or when spawned.
			virtual void BeginPlay() override;

			// Called when this Pawn is possessed.
			virtual void PossessedBy(AController * NewController) override;

			// Called when the Controller no longer possesses this pawn.
			virtual void UnPossessed() override;

	#pragma endregion

	#pragma region Sound

		private:
			
			// The FMOD component in charge of managing sound for this Pawn.
			UPROPERTY(BlueprintReadOnly, DisplayName="FMOD Audio Component", Meta=(AllowPrivateAccess=true))
			UFMODAudioComponent* FMODAudioComponent = nullptr;

		protected:

			// The FMOD Event to play on this Pawn.
			UPROPERTY(BlueprintReadOnly, Category="Sound Pawn", EditInstanceOnly, DisplayName="FMOD Event", Meta=(ExposeOnSpawn=true))
			UFMODEvent* FMODEvent = nullptr;

			// What type of SoundPawn this is.
			UPROPERTY(BlueprintReadOnly, Category="Sound Pawn", BlueprintGetter=GetSoundType, EditInstanceOnly, DisplayName="Sound Type", Meta=(ExposeOnSpawn=true))
			ESoundActorType SoundType = ESoundActorType::ST_Unspecified;

		public:

			// Get the FMOD Event.
			UFUNCTION()
			UFMODEvent* GetFMODEvent() { return this->FMODEvent; };

			// Set the FMOD Event.
			UFUNCTION()
			UFMODEvent* SetFMODEvent(UFMODEvent* Event) { this->FMODEvent = Event; return this->FMODEvent; };

			// Get the SoundType.
			UFUNCTION(BlueprintPure)
			ESoundActorType GetSoundType() const { return this->SoundType; };

			// Set the SoundType.
			UFUNCTION()
			ESoundActorType SetSoundType(ESoundActorType SoundActorType) { this->SoundType = SoundActorType; return this->SoundType; };

	#pragma endregion

	#pragma region Other

		protected:

			// The radius of the Sphere. It indirectly affects gameplay difficulty: the smaller the radius, the harder the game. Avoid changing.
			UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Sound Pawn", DisplayName="Sphere Radius", Meta=(ClampMin=0.0f, ClampMax=1000.0f))
			float SphereRadius = 35.0f;

	#pragma endregion
};
