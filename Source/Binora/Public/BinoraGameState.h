// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "BinoraLevelState.h"
#include "GameFramework/GameStateBase.h"

#include "BinoraGameState.generated.h"

/**
 * Binora's default GameState class.
 */
UCLASS()
class BINORA_API ABinoraGameState : public AGameStateBase
{
	GENERATED_BODY()

	#pragma region Level

		protected:

			// The current Level State: Narration, Memorization, Replication, Audition, or Evaluation.
			UPROPERTY(BlueprintReadOnly, Category="Binora|State", DisplayName="Level State")
			EBinoraLevelState LevelState = EBinoraLevelState::BLS_Narration;

		public:

			// Set the current Level State: Narration, Memorization, Replication, Audition, or Evaluation.
			UFUNCTION()
			void SetLevelState(EBinoraLevelState NewLevelState);

			// Get the current Level State: Narration, Memorization, Replication, Audition, or Evaluation.
			UFUNCTION()
			EBinoraLevelState GetLevelState() const;

	#pragma endregion

	#pragma region Timer

		public:

			// This should run every second.
			UFUNCTION()
			float DecrementMemorizationTimer();

			// Blueprint Event that will run once the timer is done. Has a default implementation.
			UFUNCTION(BlueprintNativeEvent, Category="Binora|Timer", DisplayName="Timer Reached Zero")
			void TimerReachedZero();

		protected:

			// The amount of time before the Memorization state is over. Replication comes next.
			UPROPERTY(BlueprintReadOnly, Category="Binora|Timer", DisplayName="Memorization Timer")
			float MemorizationTimer = 60.0f; // In seconds (one minute).

	#pragma endregion

	#pragma region Score

		public:

			// Get the players score.
			UFUNCTION()
			uint8 GetScore() const;

			// Set the player score.
			UFUNCTION()
			uint8 SetScore(uint8 NewScore);

		protected:

			// The player's score (based on the position of the SoundPawns).
			UPROPERTY()
			uint8 Score = 0;

	#pragma endregion
};
