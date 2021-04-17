// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

/**
 * An enumerator that defines the SoundPawn type.
 */
UENUM(BlueprintType)
enum class ESoundPawnType : uint8
{
	SPT_Unspecified =  0	UMETA(DisplayName="Unspecified"),
	SPT_Background1 =  1	UMETA(DisplayName="Background 1"),
	SPT_Background2	=  2	UMETA(DisplayName="Background 2"),
	SPT_Emitter1	=  3	UMETA(DisplayName="Emitter 1"),
	SPT_Emitter2	=  4	UMETA(DisplayName="Emitter 2"),
	SPT_Emitter3	=  5	UMETA(DisplayName="Emitter 3"),
	SPT_Emitter4	=  6	UMETA(DisplayName="Emitter 4"),
	SPT_Spec1		=  7	UMETA(DisplayName="Spec 1"),
	SPT_Spec2		=  8	UMETA(DisplayName="Spec 2"),
	SPT_Spec3		=  9	UMETA(DisplayName="Spec 3"),
	SPT_Spec4		= 10	UMETA(DisplayName="Spec 4")
};

// Returns the Score Category as Text.
inline FText operator *(ESoundPawnType SoundPawnType)
{
	switch (SoundPawnType)
	{
		case ESoundPawnType::SPT_Background1:	return FText::FromString(TEXT("Background 1"));
		case ESoundPawnType::SPT_Background2:	return FText::FromString(TEXT("Background 2"));
		case ESoundPawnType::SPT_Emitter1:		return FText::FromString(TEXT("Emitter 1"));
		case ESoundPawnType::SPT_Emitter2:		return FText::FromString(TEXT("Emitter 2"));
		case ESoundPawnType::SPT_Emitter3:		return FText::FromString(TEXT("Emitter 3"));
		case ESoundPawnType::SPT_Emitter4:		return FText::FromString(TEXT("Emitter 4"));
		case ESoundPawnType::SPT_Spec1:			return FText::FromString(TEXT("Spec 1"));
		case ESoundPawnType::SPT_Spec2:			return FText::FromString(TEXT("Spec 2"));
		case ESoundPawnType::SPT_Spec3:			return FText::FromString(TEXT("Spec 3"));
		case ESoundPawnType::SPT_Spec4:			return FText::FromString(TEXT("Spec 4"));
		default: 								return FText::FromString(TEXT("Invalid sound pawn type."));
	}
}

// Returns true if the value is SPT_Unspecified.
inline bool operator !(ESoundPawnType SoundPawnType)
{
	return !((bool)SoundPawnType); 
}

// Returns true if the value is NOT SPT_Unspecified.
inline bool operator ~(ESoundPawnType SoundPawnType)
{
	return (bool)SoundPawnType;
}