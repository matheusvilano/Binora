// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraGameMode.h"

#include "Kismet/GameplayStatics.h"

#pragma region Initialization

    // No-parameter constructor for objects of the ABinoraGameMoseBase class.
    ABinoraGameMode::ABinoraGameMode(){}

    // Will be used to initialize MaxScore.
    void ABinoraGameMode::BeginPlay()
    {
        
    }

    // Called during RestartPlayer to actually spawn the player's pawn, when using a start spot.
    APawn* ABinoraGameMode::SpawnDefaultPawnFor_Implementation(AController * NewPlayer,AActor * StartSpot)
    {
        if (bSpawnDefaultPawn) // Note: this is a CONSTANT and it is NOT editable in the Details panel in the editor.
        {
            return Cast<APawn>(this->AGameModeBase::GetDefaultPawnClassForController(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0)));
        }
        else
        {
            return nullptr; // In other words: DO NOT spawn any pawns.
        }
    }

#pragma endregion

#pragma region Score

    // Adds a certain number to the score.
    inline void ABinoraGameMode::AddScore(uint8 Addend)
    {
        this->Score = ((this->Score + Addend) > 100) ? 100 : this->Score + Addend;
    }

    // Returns the score as a percentage.
    inline float ABinoraGameMode::GetScoreAsPercentage() const
    {
        return 100 * this->Score / this->MaxScore;
    }

    // Adds a certain number to the score.
    inline void ABinoraGameMode::SetScore(uint8 NewScore)
    {
        // Only set the new score if it is within the 0-100 range.
        this->Score = (NewScore >= 0 && NewScore <= 100) ? NewScore : this->Score;
    }

    // Returns the score as a category (Subpar, Good, Great, or Perfect).
    EScoreCategory ABinoraGameMode::GetScoreAsCategory() const
    {
        // This will be used to get the score as a category
        uint8 ScoreAsPercentage = this->GetScoreAsPercentage();

        // Subpar
        if (ScoreAsPercentage < EScoreCategory::SC_Good)
        {
            return EScoreCategory::SC_Subpar;
        }
        // Good
        else if (ScoreAsPercentage < EScoreCategory::SC_Great)
        {
            return EScoreCategory::SC_Good;
        }
        // Great
        else if (ScoreAsPercentage < EScoreCategory::SC_Perfect)
        {
            return EScoreCategory::SC_Great;
        }
        // Perfect
        else // if the user got a perfect score (100%)
        {
            return EScoreCategory::SC_Perfect;
        }
    }

#pragma endregion

#pragma region State

    // Sets the Game Over state (generally to false).
    void ABinoraGameMode::EndGame_Implementation()
    {
        throw "To be implemented.";
    }

#pragma endregion