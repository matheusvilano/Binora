// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

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