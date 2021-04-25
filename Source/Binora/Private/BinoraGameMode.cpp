// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraGameMode.h"

#include "BinoraGameState.h"
#include "BinoraHUD.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

#pragma region Initialization

    // No-parameter constructor for objects of the ABinoraGameMoseBase class.
    ABinoraGameMode::ABinoraGameMode(){}

    // Initializes the Level State.
    void ABinoraGameMode::BeginPlay()
    {
        // Set Level State to Narration.
        this->GetGameState<ABinoraGameState>()->SetLevelState(EBinoraLevelState::BLS_Narration);
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
    void ABinoraGameMode::AddScore(uint8 Addend)
    {
        // Store the CurrentScore in a variable (for readability).
        uint8 NewScore = this->GetGameState<ABinoraGameState>()->GetScore() + Addend;

        // Set the Score on the GameState (clamp to the value of MaxScore).
        this->GetGameState<ABinoraGameState>()->SetScore((NewScore > this->MaxScore) ? this->MaxScore : NewScore);
    }

    // Returns the score as a percentage.
    float ABinoraGameMode::GetScoreAsPercentage() const
    {
        return 100 * this->GetGameState<ABinoraGameState>()->GetScore() / this->MaxScore;
    }

    // Adds a certain number to the score.
    void ABinoraGameMode::SetScore(uint8 NewScore)
    {
        // Only set the new score if it is within the 0-100 range.
        this->GetGameState<ABinoraGameState>()->SetScore((NewScore >= 0 && NewScore <= 100) ? NewScore : this->GetGameState<ABinoraGameState>()->GetScore());
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

    // Starts the memorization timer and sets the state to Memorization.
    void ABinoraGameMode::StartMemorizationTimer()
    {
        // Set the Level State to Memorization, then start decrementing the memorization time every second.
        this->GetGameState<ABinoraGameState>()->SetLevelState(EBinoraLevelState::BLS_Memorization);
        this->AActor::GetWorldTimerManager().SetTimer(this->MemorizationTimerHandle, this, &ABinoraGameMode::DecrementMemorizationTimer, 1.0f, true, 0.0f);
    }

    // The memorization timer should decrement every second.
    void ABinoraGameMode::DecrementMemorizationTimer()
    {
        // Decrement the MemorizationTimer on the GameState. If <=0, stop decrementing and set Level State to Replication. 
        if (this->GetGameState<ABinoraGameState>()->DecrementMemorizationTimer() <= 0)
        {
            // Stop decrementing the timer.
            GetWorldTimerManager().ClearTimer(this->MemorizationTimerHandle);

            // Get HUD (via PlayerController; casted to ABinoraHUD), then create the Timer widget.
            Cast<ABinoraHUD>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0)->GetHUD())->DestroyTimerWidget();

            // Update Level State to Replication
            this->GetGameState<ABinoraGameState>()->SetLevelState(EBinoraLevelState::BLS_Replication);
        
            // Blueprint event (has native implementation too).
            this->GetGameState<ABinoraGameState>()->TimerReachedZero();
        }
    }

#pragma endregion