// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraLevelBase.h"

#include "FMODEvent.h"
#include "UObject/ConstructorHelpers.h"

#pragma region Initialization

    ABinoraLevelBase::ABinoraLevelBase()
    {
        // Prevent the FMODAudioComponent from auto-playing.
        this->FMODAudioComponent = this->AActor::CreateDefaultSubobject<UFMODAudioComponent>(TEXT("FMOD Audio Component"));
		this->FMODAudioComponent->bAutoActivate = false;
    }

    void ABinoraLevelBase::BeginPlay()
    {
        // Super BeginPlay.
        Super::BeginPlay();

        // Update the FMODAudioComponent with the BeginPlay event, then play it.
        this->FMODAudioComponent->SetEvent(this->FMODEventBeginPlay);
        this->FMODAudioComponent->Play();
    }

#pragma endregion

#pragma region State

    // The GameOver event's default implementation.
    void ABinoraLevelBase::GameOver_Implementation()
    {
        // Update the FMODAudioComponent with the GameOver event, then play it.
        this->FMODAudioComponent->SetEvent(this->FMODEventGameOver);
        this->FMODAudioComponent->Play();
    }

#pragma endregion