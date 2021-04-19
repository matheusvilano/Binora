// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "BinoraPlayerController.h"

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
        this->APlayerController::SetAudioListenerOverride(nullptr, FVector(0.0f), FRotator(0.0f));

        // Get and set SoundActor references
        #pragma region SoundActors

            // Array to be used when creating SoundPawns.
            TArray<ASoundActor*> SoundActors;
        
            // Find SoundActors and add them to the SoundActors array (Cast first).
            {
                // Find SoundActors.
                TArray<AActor*> FoundActors; // Will temporarily store the actors found.
                UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASoundActor::StaticClass(), FoundActors);

                // Cast and add to array.
                for (AActor* FoundActor : FoundActors)
                {
                    SoundActors.Add(Cast<ASoundActor>(FoundActor));
                }
            }

        #pragma endregion

        // Get all actors of type ASoundActor, then create a corresponding ASoundPawn.
        for (ASoundActor* SoundActor : SoundActors)
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
    }   

#pragma endregion

#pragma region Sound

    // Spawns a SoundPawn and sets its SoundActorType and FMODEvent.
    void ABinoraPlayerController::SpawnSoundPawn(TArray<ASoundPawn*>& SoundPawnArray, ESoundActorType SoundType, UFMODEvent* FMODEvent)
    {
        if (!SoundPawnArray[*SoundType]) // only proceed if the pointer is a nullptr
        {
            SoundPawnArray[*SoundType] = Cast<ASoundPawn>(this->GetWorld()->SpawnActor<AActor>(ASoundPawn::StaticClass(), FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f)));
            SoundPawnArray[*SoundType]->SetSoundType(SoundType);
            SoundPawnArray[*SoundType]->SetFMODEvent(FMODEvent);
        }
    }

#pragma endregion