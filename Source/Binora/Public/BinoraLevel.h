// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "Engine/LevelScriptActor.h"
#include "FMODAudioComponent.h"
#include "FMODBus.h"

#include "BinoraLevel.generated.h"

#define BINORA_MAP_MAINMENU TEXT("MAP_MainMenu")
#define BINORA_MAP_BEACH 	TEXT("MAP_Beach")
#define BINORA_MAP_CABIN 	TEXT("MAP_Cabin")
#define BINORA_MAP_HOUSE 	TEXT("MAP_House")

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
			UPROPERTY(BlueprintReadOnly, Category="Binora|FMOD", DisplayName="FMOD Audio Component")
			UFMODAudioComponent* FMODAudioComponent = nullptr;

			// The opening line to be said by the narrator (brief instructions).
			UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category="Binora|FMOD", DisplayName="FMOD Event (BeginPlay)")
			UFMODEvent* FMODEventBeginPlay = nullptr;

			// The ending line to be said by the narrator (score category + thanks).
			UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category="Binora|FMOD", DisplayName="FMOD Event (GameOver)")
			UFMODEvent* FMODEventGameOver = nullptr;

			// Blueprint event that gets called once the timer starts.
			UFUNCTION(BlueprintImplementableEvent, Category="Binora|State", DisplayName="Level Started")
			void LevelStarted();

			// Blueprint event that gets called once the timer starts.
			UFUNCTION(BlueprintImplementableEvent, Category="Binora|State", DisplayName="Level Ended")
			void LevelEnded();

	#pragma endregion

	#pragma region State

		protected:

			// Callback for FMODEventBeginPlay.
			UFUNCTION()
			void OnNarrationFinished();

			// Loads the MainMenu MAP and invokes the LevelEnded event. Callback for FMODEventGameOver.
			UFUNCTION()
			void ReturnToMainMenu();

			// The GameOver event.
			UFUNCTION(BlueprintCallable, Category="Binora|State", DisplayName="Game Over")
			void GameOver();

			// The StartAudition event.
			UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Binora|State", DisplayName="Start Audition")
			void StartAudition();

			// The StopAudition event.
			UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Binora|State", DisplayName="Stop Audition")
			void StopAudition();

	#pragma endregion
};
