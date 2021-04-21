// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "Engine/LevelScriptActor.h"
#include "FMODAudioComponent.h"
#include "FMODBus.h"

#include "BinoraLevel.generated.h"

/**
 * The base code for a Binora level.
 */
UCLASS()
class BINORA_API ABinoraLevel : public ALevelScriptActor
{
	GENERATED_BODY()

	#pragma region Initialization

		public:

			// Constructor.
			ABinoraLevel();

		protected:
			
			// Called when the game starts or when spawned.
			virtual void BeginPlay() override;

	#pragma endregion
	
	#pragma region Sound

		protected:

			// The FMOD component in charge of managing the narration sound.
			UPROPERTY(BlueprintReadOnly, Category="Binora", DisplayName="FMOD Audio Component")
			UFMODAudioComponent* FMODAudioComponent = nullptr;

			// The opening line to be said by the narrator (brief instructions).
			UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category="Binora", DisplayName="FMOD Event (BeginPlay)")
			UFMODEvent* FMODEventBeginPlay = nullptr;

			// The ending line to be said by the narrator (score category + thanks).
			UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category="Binora", DisplayName="FMOD Event (GameOver)")
			UFMODEvent* FMODEventGameOver = nullptr;

			// Callback for FMODEventBeginPlay.
			UFUNCTION()
			void OnFMODEventBeginPlayStopped();

			// Callback for FMODEventGameOver.
			UFUNCTION()
			void OnFMODEventGameOverStopped();

			// Blueprint event that gets called once the timer starts.
			UFUNCTION(BlueprintImplementableEvent, Category="Binora", DisplayName="Level Started")
			void LevelStarted();

			// Blueprint event that gets called once the timer starts.
			UFUNCTION(BlueprintImplementableEvent, Category="Binora", DisplayName="Level Ended")
			void LevelEnded();

	#pragma endregion

	#pragma region State

		protected:

			// The GameOver event.
			UFUNCTION(BlueprintNativeEvent)
			void GameOver();

	#pragma endregion
};
