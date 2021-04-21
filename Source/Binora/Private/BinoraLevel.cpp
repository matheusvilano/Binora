// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraLevel.h"

#include "BinoraHUD.h"
#include "BinoraGameMode.h"
#include "FMODEvent.h"
#include "FMODBlueprintStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

#pragma region Initialization

    // Constructor
    ABinoraLevel::ABinoraLevel()
    {
        // Find FMOD Events (assets).
        static ConstructorHelpers::FObjectFinder<UFMODEvent> dFMODEventBeginPlay(TEXT("/Game/FMOD/Events/VO/AnyLevel/BeginPlay/VO_AnyLevel_BeginPlay.VO_AnyLevel_BeginPlay"));
        static ConstructorHelpers::FObjectFinder<UFMODEvent> dFMODEventGameOver(TEXT("/Game/FMOD/Events/VO/AnyLevel/GameOver/VO_GameOver.VO_GameOver"));

        // Set FMOD Events.
        this->FMODEventBeginPlay = dFMODEventBeginPlay.Object;
        this->FMODEventGameOver = dFMODEventGameOver.Object;

        // Prevent the FMODAudioComponent from auto-playing.
        this->FMODAudioComponent = this->AActor::CreateDefaultSubobject<UFMODAudioComponent>(TEXT("FMOD Audio Component"));
        this->AActor::SetRootComponent(this->FMODAudioComponent);
		this->FMODAudioComponent->bAutoActivate = false;
    }

    // Play the VO on BeginPlay
    void ABinoraLevel::BeginPlay()
    {
        // Super BeginPlay.
        Super::BeginPlay();

        // Update the FMODAudioComponent with the BeginPlay event, then play it.
        this->FMODAudioComponent->SetEvent(this->FMODEventBeginPlay);
        this->FMODAudioComponent->Play();
        this->FMODAudioComponent->OnEventStopped.AddDynamic(this, &ABinoraLevel::OnFMODEventBeginPlayStopped);
    }

#pragma endregion

#pragma region State

    // The GameOver event's default implementation.
    void ABinoraLevel::GameOver_Implementation()
    {
        // Update the FMODAudioComponent with the GameOver event, then play it.
        this->FMODAudioComponent->SetEvent(this->FMODEventGameOver);
        this->FMODAudioComponent->Play();
    }

#pragma endregion

#pragma region Sound

    // Callback for FMODEventBeginPlay.
	void ABinoraLevel::OnFMODEventBeginPlayStopped()
    {
        // Start the Memorization Timer.
        Cast<ABinoraGameMode>(UGameplayStatics::GetGameMode(this->AActor::GetWorld()))->StartMemorizationTimer();

        // Get HUD (via PlayerController; casted to ABinoraHUD), then create the Timer widget.
        Cast<ABinoraHUD>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0)->GetHUD())->CreateTimerWidget();

        // Blueprint Event.
        this->LevelStarted();
    }

    // Callback for FMODEventGameOver.
    void ABinoraLevel::OnFMODEventGameOverStopped()
    {
        // Blueprint Event.
        this->LevelEnded();
    }

#pragma endregion