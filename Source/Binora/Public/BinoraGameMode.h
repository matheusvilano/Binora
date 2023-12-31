// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "ScoreCategory.h"

#include "BinoraGameMode.generated.h"

/**
 * The base game mode for Binora. ORA ORA ORA. If you know what I mean.
 */
UCLASS()
class BINORA_API ABinoraGameMode : public AGameModeBase
{
	GENERATED_BODY()

	#pragma region Initialization

		public:

			// No-parameter constructor for objects of the ABinoraGameMoseBase class.
			ABinoraGameMode();

		protected:

			// Will be used to initialize MaxScore.
			virtual void BeginPlay() override;

			// Called during RestartPlayer to actually spawn the player's pawn, when using a start spot.
			virtual APawn* SpawnDefaultPawnFor_Implementation(AController* NewPlayer, class AActor* StartSpot) override;

	#pragma endregion

	#pragma region Score

		public:

			// The player's score (based on the position of the SoundPawns). 
			static const uint8 MaxScore = 30;

		protected:

			// Adds a certain number to the score.
			UFUNCTION(BlueprintCallable, Category="Binora|Score")
			void AddScore(uint8 Addend);

			// Sets the score.
			UFUNCTION(BlueprintCallable, Category="Binora|Score")
			void SetScore(uint8 NewScore);

			// Returns the score as a percentage.
			UFUNCTION(BlueprintCallable, BlueprintPure, Category="Binora|Score")
			float GetScoreAsPercentage() const;

			// Returns the score as a category (Subpar, Good, Great, or Perfect).
			UFUNCTION(BlueprintCallable, BlueprintPure, Category="Binora|Score")
			EScoreCategory GetScoreAsCategory() const;

	#pragma region State

		public:

			// Sets the Game Over state (generally to false).
			UFUNCTION(BlueprintImplementableEvent)
			void EndGame();

	#pragma endregion

	#pragma region Timer

		protected:

		    // Handle to be used by the Time Manager
        	UPROPERTY()
			FTimerHandle MemorizationTimerHandle;

			// This should run every second.
			UFUNCTION()
			void DecrementMemorizationTimer();

		public:
		
			// Starts the memorization timer and sets the state to Memorization.
			UFUNCTION()
			void StartMemorizationTimer();

	#pragma endregion

	#pragma region Other

		private:

			// Whether or not to spawn a pawn of the Default Pawn Class once the game starts.
			const bool bSpawnDefaultPawn = false;

	#pragma endregion
};
