// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#include "TutorialSubtitles.h"

#include "FMODEvent.h"
#include "UObject/ConstructorHelpers.h"

#pragma region Initialization

	// Sets default values
	ATutorialSubtitles::ATutorialSubtitles()
	{
		// Set this actor NOT to call Tick() every frame. 
		this->AActor::PrimaryActorTick.bCanEverTick = false;

		// Set up FMOD Component
		this->FMODAudioComponent = this->UObject::CreateDefaultSubobject<UFMODAudioComponent>(TEXT("FMOD Audio Component"));
		this->AActor::SetRootComponent(this->FMODAudioComponent);

		// Find FMOD Event (asset); use as default. "_C" and "UClass" (instead of "UFMODEvent") ensures that it will (also) work on a packaged build. NOTE: Only working in the editor, as FMOD references are NOT packaged.
        // static ConstructorHelpers::FObjectFinder<UFMODEvent> dFMODEvent(TEXT("/Game/FMOD/Events/VO/MainMenu/Tutorial/VO_MainMenu_TutorialSection"));
		// this->FMODAudioComponent->SetEvent(dFMODEvent.Object);

		// Set up FMOD Callbacks
		this->FMODAudioComponent->bEnableTimelineCallbacks = true;
		this->FMODAudioComponent->OnTimelineMarker.AddDynamic(this, &ATutorialSubtitles::UpdateCurrentLine);
	}

	// Construction script
	void ATutorialSubtitles::OnConstruction(const FTransform& Transform)
	{
		this->FMODAudioComponent->SetEvent(this->FMODEvent);
	}

#pragma endregion

#pragma region Subtitles

	// Updates the subtitles corresponding to a FMOD Timeline Marker. The timeline position is unused, but necessary for the callback.
	void ATutorialSubtitles::UpdateCurrentLine(FString MarkerName, int32 TimelinePosition)
	{
		if 		(MarkerName == "A")	this->CurrentLine = TEXT("Binora is an audio puzzle game where the objective is to recreate a Soundscape.");
		else if (MarkerName == "B")	this->CurrentLine = TEXT("Once you select a level, you will be presented with a complete Soundscape composed of 10 sounds of 3 different types:");
		else if (MarkerName == "C")	this->CurrentLine = TEXT("2 Backgrounds, 4 Emitters, and 4 Specifics.");
		else if (MarkerName == "D")	this->CurrentLine = TEXT("A Background is a multi-sourced constant 'bed' for a Soundscape - say, for example, the sound of traffic.");
		else if (MarkerName == "E")	this->CurrentLine = TEXT("An Emitter is a single-sourced constant emitting sound - say, for example, a camp fire.");
		else if (MarkerName == "F")	this->CurrentLine = TEXT("Finally, a Specific is an intermittent sound - say, for example, a dog barking.");
		else if (MarkerName == "G")	this->CurrentLine = TEXT("You will have a certain amount of time to listen to and memorize the Soundscape.");
		else if (MarkerName == "H")	this->CurrentLine = TEXT("Once the time is up, all sounds will fade away, and you will be tasked with recreating the Soundscape.");
		else if (MarkerName == "I")	this->CurrentLine = TEXT("At first, all sounds will be muted, and positioned in the centre of the Soundscape.");
		else if (MarkerName == "J")	this->CurrentLine = TEXT("You can use your controller to activate the sounds:");
		else if (MarkerName == "K")	this->CurrentLine = TEXT("Trigger Buttons for Backgrounds, D-pad Buttons for Specifics, and Face Buttons for Emitters.");
		else if (MarkerName == "L")	this->CurrentLine = TEXT("Once an element has been activated, you may control its volume and direction using any of the Thumbsticks.");
		else if (MarkerName == "M")	this->CurrentLine = TEXT("Up-and-Down controls volume, and Left-and-Right controls direction.");
		else if (MarkerName == "N")	this->CurrentLine = TEXT("Additionally, you may use any of the Shoulder Buttons to audit your Soundscape.");
		else if (MarkerName == "O")	this->CurrentLine = TEXT("The closer you are to the original Soundscape, the higher your score.");
		else if (MarkerName == "P")	this->CurrentLine = TEXT("Goodluck!");
		else						this->CurrentLine = TEXT("Tutorial");
	}

#pragma endregion