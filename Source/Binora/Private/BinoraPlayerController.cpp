// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraPlayerController.h"

#include "Delegates/DelegateInstancesImpl.h"
#include "Engine/InputDelegateBinding.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

#pragma region Inherited

    ABinoraPlayerController::ABinoraPlayerController()
    {
        // Initialize array (set sizes; populate with nullptrs).
        this->Backgrounds.Init(nullptr, 2);
        this->Emitters.Init(nullptr, 4);
        this->Specs.Init(nullptr, 4);
    }

    void ABinoraPlayerController::BeginPlay()
    {
        // Set AudioListener to centre of the MAP (world coordinates).
        this->APlayerController::SetAudioListenerOverride(nullptr, FVector(-100.0f, 0.0f, 0.0f), FRotator(0.0f));

        // Set the ASoundPawn class to spawn, according to the GameMode settings.
        this->SoundPawnClass = UGameplayStatics::GetGameMode(this->AActor::GetWorld())->GetDefaultPawnClassForController(this);

        // Get and set SoundActor references
        #pragma region Actors
        {
            // Find SoundActors and add them to the SoundActors array (Cast first).
            TArray<AActor*> FoundActors; // Will temporarily store the actors found.
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundActor::StaticClass(), FoundActors);

            // Cast and add to array.
            for (AActor* FoundActor : FoundActors)
            {
                this->SoundActors.Add(Cast<ASoundActor>(FoundActor));
            }
        }
        #pragma endregion

        // Spawn SoundPawns
        #pragma region SoundPawns

            // Get all actors of type ASoundActor, then create a corresponding ASoundPawn.
            for (ASoundActor* SoundActor : this->SoundActors)
            {
                switch (SoundActor->GetSoundType())
                {
                    case ESoundActorType::ST_Background1:
                        this->SpawnSoundPawn(this->Backgrounds, ESoundActorType::ST_Background1, SoundActor->GetFMODEvent());
                        break;

                    case ESoundActorType::ST_Background2:
                        this->SpawnSoundPawn(this->Backgrounds, ESoundActorType::ST_Background2, SoundActor->GetFMODEvent());
                        break;
                    
                    case ESoundActorType::ST_Emitter1:
                        this->SpawnSoundPawn(this->Emitters, ESoundActorType::ST_Emitter1, SoundActor->GetFMODEvent());
                        break;
                    
                    case ESoundActorType::ST_Emitter2:
                        this->SpawnSoundPawn(this->Emitters, ESoundActorType::ST_Emitter2, SoundActor->GetFMODEvent());
                        break;
                    
                    case ESoundActorType::ST_Emitter3:
                        this->SpawnSoundPawn(this->Emitters, ESoundActorType::ST_Emitter3, SoundActor->GetFMODEvent());
                        break;
                    
                    case ESoundActorType::ST_Emitter4:
                        this->SpawnSoundPawn(this->Emitters, ESoundActorType::ST_Emitter4, SoundActor->GetFMODEvent());
                        break;
                    
                    case ESoundActorType::ST_Spec1:
                        this->SpawnSoundPawn(this->Specs, ESoundActorType::ST_Spec1, SoundActor->GetFMODEvent());
                        break;
                    
                    case ESoundActorType::ST_Spec2:
                        this->SpawnSoundPawn(this->Specs, ESoundActorType::ST_Spec2, SoundActor->GetFMODEvent());
                        break;
                    
                    case ESoundActorType::ST_Spec3:
                        this->SpawnSoundPawn(this->Specs, ESoundActorType::ST_Spec3, SoundActor->GetFMODEvent());
                        break;
                    
                    case ESoundActorType::ST_Spec4:
                        this->SpawnSoundPawn(this->Specs, ESoundActorType::ST_Spec4, SoundActor->GetFMODEvent());
                        break;

                    default:
                        // Will add a Warning message later.
                        break;
                }
            }

        #pragma endregion
    }   

    void ABinoraPlayerController::SetupInputComponent()
    {
        Super::SetupInputComponent();

        // Make sure the input component doesn't already exist
        if (!this->BinoraInputComponent)
        {
            // Initialize
            this->BinoraInputComponent = NewObject<UBinoraInputComponent>(this);
            this->BinoraInputComponent->RegisterComponent();
            this->BinoraInputComponent->bBlockInput = false;
            this->BinoraInputComponent->Priority = 0;

            // Set up delegates
            if (UInputDelegateBinding::SupportsInputDelegate(this->GetClass()))
            {
                UInputDelegateBinding::BindInputDelegates(this->GetClass(), this->BinoraInputComponent);
            }

            // Push onto the stack
            this->APlayerController::PushInputComponent(this->BinoraInputComponent);

            // Set up bindings
            {
                // Backgrounds
                this->BinoraInputComponent->BindAction("SelectBackground1", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Backgrounds[*ESoundActorType::ST_Background1]);});
                this->BinoraInputComponent->BindAction("SelectBackgorund2", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Backgrounds[*ESoundActorType::ST_Background2]);});

                // Emitters
                this->BinoraInputComponent->BindAction("SelectEmitter1", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Emitters[*ESoundActorType::ST_Emitter1]);});
                this->BinoraInputComponent->BindAction("SelectEmitter2", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Emitters[*ESoundActorType::ST_Emitter2]);});
                this->BinoraInputComponent->BindAction("SelectEmitter3", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Emitters[*ESoundActorType::ST_Emitter3]);});
                this->BinoraInputComponent->BindAction("SelectEmitter4", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Emitters[*ESoundActorType::ST_Emitter4]);});

                // Specs
                this->BinoraInputComponent->BindAction("SelectSpec1", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Specs[*ESoundActorType::ST_Spec1]);});
                this->BinoraInputComponent->BindAction("SelectSpec2", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Specs[*ESoundActorType::ST_Spec2]);});
                this->BinoraInputComponent->BindAction("SelectSpec3", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Specs[*ESoundActorType::ST_Spec3]);});
                this->BinoraInputComponent->BindAction("SelectSpec4", EInputEvent::IE_Pressed, this, [this](){this->APlayerController::Possess(this->Specs[*ESoundActorType::ST_Spec4]);});
            }
        }
    }

#pragma endregion

#pragma region Sound

    // Spawns a SoundPawn and sets its SoundActorType and FMODEvent.
    void ABinoraPlayerController::SpawnSoundPawn(TArray<ASoundPawn*>& SoundPawnArray, ESoundActorType SoundType, UFMODEvent* FMODEvent)
    {
        if (!SoundPawnArray[*SoundType]) // only proceed if the pointer is a nullptr
        {
            SoundPawnArray[*SoundType] = Cast<ASoundPawn>(this->GetWorld()->SpawnActor<AActor>(SoundPawnClass, FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f)));
            SoundPawnArray[*SoundType]->SetSoundType(SoundType);
            SoundPawnArray[*SoundType]->GetFMODAudioComponent()->SetEvent(FMODEvent);
            SoundPawnArray[*SoundType]->SetActorLabel(~SoundType); // This renames the Actor (so that it is easy to find it in the World Outliner).
        }
    }

    // Get the Sound Actors.
    TArray<ASoundActor*> ABinoraPlayerController::GetSoundActors()
    {
        return this->SoundActors;
    }

#pragma endregion