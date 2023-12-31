// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraGameState.h"

#include "BinoraPlayerController.h"
#include "Kismet/GameplayStatics.h"

#pragma region State

    // Gets the current level state.
    EBinoraLevelState ABinoraGameState::GetLevelState() const
    {
        return this->LevelState;
    }

    // Sets the new level state.
    void ABinoraGameState::SetLevelState(EBinoraLevelState NewLevelState)
    { 
        // Set Level State
        this->LevelState = NewLevelState; 

        // Get Player Controller
        ABinoraPlayerController* BinoraPlayerController = Cast<ABinoraPlayerController>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0));

        switch(this->LevelState)
        {
            case EBinoraLevelState::BLS_Narration:
            {
                // Make sure input is disable during Narration
                BinoraPlayerController->DisableAllSoundPawns();
                break;
            }
            case EBinoraLevelState::BLS_Memorization:
            {
                // Make sure input is still disable during Memorization
                BinoraPlayerController->DisableAllSoundPawns();
                break;
            }
            case EBinoraLevelState::BLS_Replication:
            {
                // Enable input during Replication
                BinoraPlayerController->EnableAllSoundPawns();
                break;
            }
            case EBinoraLevelState::BLS_Audition:
            {
                // Make sure input is still disable during Audition
                BinoraPlayerController->EnableAllSoundPawns();
                break;
            }
            case EBinoraLevelState::BLS_Evaluation:
            {
                // Make sure input is still disable during Evaluation
                BinoraPlayerController->DisableAllSoundPawns();
                break;
            }
            default:
            {
                UE_LOG(LogTemp, Warning, TEXT("Invalid Level State encountered. The game may not behave as expected from this point on."));
                break;
            }
        }
    }

#pragma endregion

#pragma region Timer

    // Set the timer.
    float ABinoraGameState::SetMemorizationTimer(float NewTimeInSeconds)
    {
        this->MemorizationTimer = NewTimeInSeconds;
        return this->MemorizationTimer;
    }

    // Decrement the timer by 1 (second).
	float ABinoraGameState::DecrementMemorizationTimer() 
    { 
        return --this->MemorizationTimer; 
    }

    // Blueprint Event that will run the timer has reached zero.
    void ABinoraGameState::TimerReachedZero_Implementation()
    {
        // Stop every SoundActor FMOD Event.
        for (ASoundActor* SoundActor : Cast<ABinoraPlayerController>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0))->GetSoundActors())
        {
            SoundActor->GetFMODAudioComponent()->Stop(); 
        }
    }

#pragma endregion

#pragma region Score

    // Get the player score.
    uint8 ABinoraGameState::GetScore() const
    {
        return this->Score;
    }

    // Set the player score.
    uint8 ABinoraGameState::SetScore(uint8 NewScore)
    {
        this->Score = NewScore;
        return this->Score;
    }

#pragma endregion