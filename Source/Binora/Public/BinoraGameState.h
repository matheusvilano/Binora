// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "BinoraLevelState.h"
#include "FMODBus.h"
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
			UPROPERTY(BlueprintReadOnly, DisplayName="Level State")
			EBinoraLevelState LevelState = EBinoraLevelState::BLS_Narration;

		public:

			// The current Level State: Narration, Memorization, Replication, Audition, or Evaluation.
			UFUNCTION()
			void SetLevelState(EBinoraLevelState NewLevelState);

	#pragma endregion

	#pragma region Timer

		public:

			// This should run every second.
			UFUNCTION()
			float DecrementMemorizationTimer();

		protected:

			// The amount of time before the Memorization state is over. Replication comes next.
			UPROPERTY(BlueprintReadOnly, DisplayName="Memorization Timer")
			float MemorizationTimer = 60.0f; // In seconds (one minute).

	#pragma endregion
};
