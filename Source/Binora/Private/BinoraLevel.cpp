// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraLevel.h"

#include "Blueprint/UserWidget.h"
#include "BinoraHUD.h"
#include "BinoraGameMode.h"
#include "BinoraGameState.h"
#include "BinoraLevelState.h"
#include "BinoraPlayerController.h"
#include "FMODEvent.h"
#include "FMODBlueprintStatics.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/SoftObjectPath.h"

#pragma region Initialization

    // Constructor
    ABinoraLevel::ABinoraLevel()
    {
        // Get default visuals (if existent). Set in BP if necessary.
        this->LevelWidget = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("/Game/Blueprints/Widgets/WBP_LevelBackground")).Class;

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

        // Load visuals (widget): create, then add to viewport.
        if (!this-bIncludeVisuals)
        {
            CreateWidget(this->AActor::GetWorld(), this->LevelWidget)->AddToViewport(0);
        }

        // Update the FMODAudioComponent with the BeginPlay event.
        this->FMODAudioComponent->SetEvent(this->FMODEventBeginPlay);

        // Automatically handle the Timer once the VO (BeginPlay) is done.
        this->FMODAudioComponent->OnEventStopped.AddDynamic(this, &ABinoraLevel::OnNarrationFinished);

        // Play the VO (BeginPlay).
        this->FMODAudioComponent->Play();

        // Bind the Confirm action to the GameOver function.
        this->AActor::InputComponent->BindAction("Confirm", EInputEvent::IE_Pressed, this, &ABinoraLevel::GameOver);

        // Bind the Return action to the ReturnToMainMenuFunction.

        // Bind the Audit action to the AuditPawns function.
        this->AActor::InputComponent->BindAction("Audit", EInputEvent::IE_Pressed, this, &ABinoraLevel::StartAudition);
        this->AActor::InputComponent->BindAction("Audit", EInputEvent::IE_Released, this, &ABinoraLevel::StopAudition);
    }

#pragma endregion

#pragma region State

    // The StartAudition event.
    void ABinoraLevel::StartAudition_Implementation()
    {
        // Get Binora Game State
        ABinoraGameState* BinoraGameState = Cast<ABinoraGameState>(UGameplayStatics::GetGameState(this->GetWorld()));

        // Get current Level State from BinoraGameState.
        EBinoraLevelState CurrentLevelState = BinoraGameState->GetLevelState();

        // Update Level State.
        switch (CurrentLevelState)
        {
            case EBinoraLevelState::BLS_Replication:
            case EBinoraLevelState::BLS_Audition:
            {
                // Update Level State
                BinoraGameState->SetLevelState(EBinoraLevelState::BLS_Audition);

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
        // Get Binora Game State
        ABinoraGameState* BinoraGameState = Cast<ABinoraGameState>(UGameplayStatics::GetGameState(this->GetWorld()));

        // Get current state from BinoraGameState.
        EBinoraLevelState CurrentLevelState = BinoraGameState->GetLevelState();

        // Update Level State.
        switch (CurrentLevelState)
        {
            case EBinoraLevelState::BLS_Replication:
            case EBinoraLevelState::BLS_Audition:
            {
                // Update Level State
                BinoraGameState->SetLevelState(EBinoraLevelState::BLS_Replication);

                // Get Player Controller
                ABinoraPlayerController* BinoraPlayerController = Cast<ABinoraPlayerController>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0));

                // Stop all SoundPawns.
                BinoraPlayerController->StopAllSoundPawns();

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
        // Get Binora Game State
        ABinoraGameState* BinoraGameState = Cast<ABinoraGameState>(UGameplayStatics::GetGameState(this->GetWorld()));

        // Get current Level State from BinoraGameState.
        EBinoraLevelState CurrentLevelState = BinoraGameState->GetLevelState();

        // Update Level State.
        switch (CurrentLevelState)
        {
            case EBinoraLevelState::BLS_Replication:
            case EBinoraLevelState::BLS_Audition:
            {
                // Update Level State
                BinoraGameState->SetLevelState(EBinoraLevelState::BLS_Evaluation);

                // Inform the GameMode that the user has pressed the Confirm button, so the level is ending. The GameMode will calculate the score and define performance.
                Cast<ABinoraGameMode>(UGameplayStatics::GetGameMode(this->GetWorld()))->EndGame();

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

#pragma region Callbacks

    // Callback for FMODEventBeginPlay.
	void ABinoraLevel::OnNarrationFinished()
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
            this->FMODAudioComponent->OnEventStopped.AddDynamic(this, &ABinoraLevel::ReturnToMainMenu);
        }

        // Start the Memorization Timer.
        Cast<ABinoraGameMode>(UGameplayStatics::GetGameMode(this->AActor::GetWorld()))->StartMemorizationTimer();

        // Get HUD (via PlayerController; casted to ABinoraHUD), then create the Timer widget.
        Cast<ABinoraHUD>(UGameplayStatics::GetPlayerController(this->AActor::GetWorld(), 0)->GetHUD())->CreateTimerWidget();

        // Blueprint Event.
        this->LevelStarted();
    }

    // Loads the MainMenu MAP and invokes the LevelEnded event. Callback for FMODEventGameOver.
    void ABinoraLevel::ReturnToMainMenu()
    {
        // Load the main menu
        UGameplayStatics::OpenLevel(this->AActor::GetWorld(), BINORA_MAP_MAINMENU);

        // Blueprint Event.
        this->LevelEnded();
    }

#pragma endregion