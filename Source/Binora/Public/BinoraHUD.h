// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BinoraHUD.generated.h"

/**
 * Binora's base HUD class.
 */
UCLASS()
class BINORA_API ABinoraHUD : public AHUD
{
	GENERATED_BODY()
	
	#pragma region Widget

		public:

			// Generates the Timer widget.
			UFUNCTION(BlueprintImplementableEvent, Category="Binora", DisplayName="Create Timer Widget")
			void CreateTimerWidget();

			// Generates the Timer widget.
			UFUNCTION(BlueprintImplementableEvent, Category="Binora", DisplayName="Destroy Timer Widget")
			void DestroyTimerWidget();

	#pragma endregion
};
