// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "Containers/Array.h"
#include "SoundActor.h"
#include "SoundPawn.h"
#include "GameFramework/PlayerController.h"

#include "BinoraPlayerController.generated.h"

#pragma region Declaration

	class ASoundActor;
	class ASoundPawn;

#pragma endregion

/**
 * 
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

	#pragma endregion
};
