// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "Containers/UnrealString.h"
#include "GameFramework/Actor.h"
#include "FMODAudioComponent.h"

#include "TutorialSubtitles.generated.h"

UCLASS()
class BINORA_API ATutorialSubtitles : public AActor
{
	GENERATED_BODY()
	
	#pragma region Initialization

		public:	

			// Sets default values for this actor's properties
			ATutorialSubtitles();

	#pragma endregion

	#pragma region Sound

		protected:

			// The FMOD Audio Component in charge of handling the Tutorial VO.
			UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Binora|Tutorial", DisplayName="FMOD Audio Component")
			UFMODAudioComponent* FMODAudioComponent = nullptr;

			// Updates the currnet line corresponding to a FMOD Timeline Marker. The timeline position is unused, but necessary for the callback.
			UFUNCTION()
			void UpdateCurrentLine(FString MarkerName, int32 TimelinePosition);

			// The current line
			UPROPERTY(BlueprintReadOnly, Category="Binora|Tutorial", DisplayName="Current Line")
			FString CurrentLine;

	#pragma endregion
};
