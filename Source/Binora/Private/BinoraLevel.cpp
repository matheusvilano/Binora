// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraLevel.h"

#include "BinoraHUD.h"
#include "BinoraGameMode.h"
#include "BinoraGameState.h"
#include "BinoraLevelState.h"
#include "BinoraPlayerController.h"
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

        // Update the FMODAudioComponent with the BeginPlay event.
        this->FMODAudioComponent->SetEvent(this->FMODEventBeginPlay);

        // Automatically handle the Timer once the VO (BeginPlay) is done.
        this->FMODAudioComponent->OnEventStopped.AddDynamic(this, &ABinoraLevel::OnFMODEventBeginPlayStopped);

        // Play the VO (BeginPlay).
        this->FMODAudioComponent->Play();

        // Bind the Confirm action to the GameOver function.
        this->AActor::InputComponent->BindAction("Confirm", EInputEvent::IE_Pressed, this, &ABinoraLevel::GameOver);

        // Bind the Audit action to the AuditPawns function.
        this->AActor::InputComponent->BindAction("Audit", EInputEvent::IE_Pressed, this, &ABinoraLevel::StartAudition);
        this->AActor::InputComponent->BindAction("Audit", EInputEvent::IE_Released, this, &ABinoraLevel::StopAudition);
    }

#pragma endregion

#pragma region State

    // The StartAudition event.
    void ABinoraLevel::StartAudition_Implementation()
    {
        // Get current Level State from BinoraGameState.
        EBinoraLevelState CurrentLevelState = Cast<ABinoraGameState>(UGameplayStatics::GetGameState(this->GetWorld()))->GetLevelState();

        // Update Level State.
        switch (CurrentLevelState)
        {
            case EBinoraLevelState::BLS_Replication:
            case EBinoraLevelState::BLS_Audition:
            {
                // Get Player Controller
                ABinoraPlayerController* BinoraPlayerController = Cast<ABinoraPlayerController>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0));

                // Stop all SoundPawns.
                BinoraPlayerController->PlayAllSoundPawns();

                break;
            }
            default:
            {
                // Will add a Warning message here later.
                break;
            }
        }
    }

    // The StopAudition event.
    void ABinoraLevel::StopAudition_Implementation()
    {
        // Get current state from BinoraGameState.
        EBinoraLevelState CurrentLevelState = Cast<ABinoraGameState>(UGameplayStatics::GetGameState(this->GetWorld()))->GetLevelState();

        // Update Level State.
        switch (CurrentLevelState)
        {
            case EBinoraLevelState::BLS_Replication:
            case EBinoraLevelState::BLS_Audition:
            {
                // Get Player Controller
                ABinoraPlayerController* BinoraPlayerController = Cast<ABinoraPlayerController>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0));

                // Stop all SoundPawns.
                BinoraPlayerController->StopAllSoundPawns();

                // Play all SoundActors.
                break;
            }
            default:
            {
                // Will add a Warning message here later.
                break;
            }
        }
    }

    // The GameOver event's default implementation.
    void ABinoraLevel::GameOver()
    {
        // Get current state from BinoraGameState.
        EBinoraLevelState CurrentLevelState = Cast<ABinoraGameState>(UGameplayStatics::GetGameState(this->GetWorld()))->GetLevelState();

        // Update Level State.
        switch (CurrentLevelState)
        {
            case EBinoraLevelState::BLS_Replication:
            case EBinoraLevelState::BLS_Audition:
            {
                // Stop all SoundPawns.
                Cast<ABinoraPlayerController>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0))->StopAllSoundPawns();

                // Make sure the FMODAudioComponent has the GameOver event, then play it.
                this->FMODAudioComponent->SetEvent(this->FMODEventGameOver); // Not necessary, but good to have.
                this->FMODAudioComponent->Play();
                break;
            }
            default:
            {
                // Will add a Warning message here later.
                break;
            }
        }
    }

#pragma endregion

#pragma region Sound

    // Callback for FMODEventBeginPlay.
	void ABinoraLevel::OnFMODEventBeginPlayStopped()
    {
        // New audio settings (change VO from BeginPlay to GameOver)
        {
            // Remove all previous bindings.
            this->FMODAudioComponent->OnEventStopped.RemoveAll(this);

            // Update the FMODAudioComponent with the GameOver event.
            this->FMODAudioComponent->SetEvent(this->FMODEventGameOver);

            // Make sure no sound is still playing (VO lines are overlapping if the game stops while a line is already happening).
            this->FMODAudioComponent->Stop();

            // Automatically load the Main Menu once the game is over.
            this->FMODAudioComponent->OnEventStopped.AddDynamic(this, &ABinoraLevel::OnFMODEventGameOverStopped);
        }

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
        // Load the main menu
        UGameplayStatics::OpenLevel(this->AActor::GetWorld(), BINORA_MAP_MAINMENU);

        // Blueprint Event.
        this->LevelEnded();
    }

#pragma endregion