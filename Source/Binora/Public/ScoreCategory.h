// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"
#include "Internationalization/Text.h"

/**
 * An enumerator that defines score categories.
 * In other words, it converts numeric data into categorical data.
 * Note: this considers the Score as a percentage.
 */
UENUM(BlueprintType)
enum class EScoreCategory : uint8
{
	SC_Subpar = 0		UMETA(DisplayName="Subpar"),
	SC_Good = 25		UMETA(DisplayName="Good"),
	SC_Great = 50		UMETA(DisplayName="Great"),
	SC_Perfect = 100	UMETA(DisplayName="Perfect")
};

// Returns the Score Category as Text.
inline FText operator *(EScoreCategory ScoreCategory)
{
	switch (ScoreCategory)
	{
		case EScoreCategory::SC_Subpar: 	return FText::FromString(TEXT("Subpar!"));
		case EScoreCategory::SC_Good:		return FText::FromString(TEXT("Good!"));
		case EScoreCategory::SC_Great:		return FText::FromString(TEXT("Great!"));
		case EScoreCategory::SC_Perfect:	return FText::FromString(TEXT("Perfect!"));
		default: 							return FText::FromString(TEXT("Invalid score category."));
	}
}

// Defines the < operator for uint8 < EScoreCategory
inline bool operator <(uint8 Integer, EScoreCategory ScoreCategory)
{
	return Integer < (uint8)ScoreCategory;
}

// Defines the <= operator for uint8 < EScoreCategory
inline bool operator <=(uint8 Integer, EScoreCategory ScoreCategory)
{
	return Integer <= (uint8)ScoreCategory;
}

// Defines the > operator for uint8 < EScoreCategory
inline bool operator >(uint8 Integer, EScoreCategory ScoreCategory)
{
	return Integer > (uint8)ScoreCategory;
}

// Defines the >= operator for uint8 < EScoreCategory
inline bool operator >=(uint8 Integer, EScoreCategory ScoreCategory)
{
	return Integer >= (uint8)ScoreCategory;
}

// Defines the == operator for uint8 < EScoreCategory
inline bool operator ==(uint8 Integer, EScoreCategory ScoreCategory)
{
	return Integer == (uint8)ScoreCategory;
}

// Defines the != operator for uint8 < EScoreCategory
inline bool operator !=(uint8 Integer, EScoreCategory ScoreCategory)
{
	return Integer != (uint8)ScoreCategory;
}