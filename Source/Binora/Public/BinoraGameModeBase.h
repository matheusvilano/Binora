// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScoreCategory.h"
#include "BinoraGameModeBase.generated.h"

/**
 * The base game mode for Binora. ORA ORA ORA. If you know what I mean.
 */
UCLASS()
class BINORA_API ABinoraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Constructors

	public:

		// No-parameter constructor for objects of the ABinoraGameMoseBase class.
		ABinoraGameModeBase();

#pragma endregion

#pragma region Framework

	protected:

		// Will be used to initialize MaxScore
		virtual void BeginPlay() override;

#pragma endregion

#pragma region Score

	protected:

		// The player's score (based on the position of the SoundPawns). 
		UPROPERTY(BlueprintReadOnly, DisplayName="Score", Meta=(ClampMin=0, ClampMax=100))
		uint8 Score = 0;

		// The player's score (based on the position of the SoundPawns). 
		UPROPERTY(BlueprintReadOnly, DisplayName="Max Score", Meta=(ClampMin=0, ClampMax=100))
		uint8 MaxScore = 100;

		// Adds a certain number to the score.
		UFUNCTION()
		void AddScore(uint8 Addend);

		// Returns the score as a percentage.
		UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetScoreAsPercentage() const;

		// Returns the score as a category (Subpar, Good, Great, or Perfect).
		UFUNCTION(BlueprintCallable, BlueprintPure)
		EScoreCategory GetScoreAsCategory() const;

#pragma region State

	protected:
		
		// Whether or not the game is over.
		UPROPERTY(BlueprintReadOnly, DisplayName="Game Over State")
		bool bGameOver = false;

		// Sets the Game Over state (generally to false).
		// UFUNCTION(BlueprintNativeEvent, Exec)
		// void SetGameOver(bool bGameOverState = false);
};
