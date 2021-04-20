// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "BinoraInputComponent.h"
#include "Containers/Array.h"
#include "SoundActor.h"
#include "SoundPawn.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"

#include "BinoraPlayerController.generated.h"

#pragma region Declaration

	class UBinoraInputComponent;
	class ASoundActor;
	class ASoundPawn;

#pragma endregion

/**
 * Binora's default Player Controller.
 */
UCLASS()
class BINORA_API ABinoraPlayerController : public APlayerController
{
	GENERATED_BODY()

	#pragma region Initialization

		public:

			// Constructor to set defaults
			ABinoraPlayerController();

		protected:
			
			// Called when the game starts or when spawned
			virtual void BeginPlay() override;

			// Setup the BinoraInputComponent.
			virtual void SetupInputComponent() override;

	#pragma endregion

	#pragma region Sound
	
		protected:

			// The Background SoundPawns.
			UPROPERTY(BlueprintReadOnly, DisplayName="Backgrounds")
			TArray<ASoundPawn*> Backgrounds;

			// The Emitter SoundPawns.
			UPROPERTY(BlueprintReadOnly, DisplayName="Emitters")
			TArray<ASoundPawn*> Emitters;

			// The Specific SoundPawns.
			UPROPERTY(BlueprintReadOnly, DisplayName="Specifics")
			TArray<ASoundPawn*> Specs;

			// Spawns a SoundPawn and sets its SoundActorType and FMODEvent.
			UFUNCTION()
			void SpawnSoundPawn(TArray<ASoundPawn*>& SoundPawnArray, ESoundActorType SoundType, UFMODEvent* FMODEvent);

			// The class of ASoundPawn to spawn.
			UPROPERTY()
			TSubclassOf<ASoundPawn> SoundPawnClass;

	#pragma endregion

	#pragma region Bindings

		protected:

			// Binora's custom input component (supports Lambdas).
			UPROPERTY()
			UBinoraInputComponent* BinoraInputComponent = nullptr;

	#pragma endregion
};
