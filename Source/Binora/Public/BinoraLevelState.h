// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

/**
 * Represents a Binora Game State.
 */
UENUM(BlueprintType)
enum class EBinoraLevelState : uint8
{
    BLS_Narration       UMETA(DisplayName="Narration"),
    BLS_Memorization    UMETA(DisplayName="Memorization"),
    BLS_Replication     UMETA(DisplayName="Replication"),
    BLS_Audition        UMETA(DisplayName="Audition"),
    BLS_Evaluation      UMETA(DisplayName="Evaluation")
};
