// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

/**
 * An enumerator that defines the sound type.
 */
UENUM(BlueprintType)
enum class ESoundActorType : uint8
{
	ST_Unspecified	=  0	UMETA(DisplayName="Unspecified"),
	ST_Background1	=  1	UMETA(DisplayName="Background 1"),
	ST_Background2	=  2	UMETA(DisplayName="Background 2"),
	ST_Emitter1		=  3	UMETA(DisplayName="Emitter 1"),
	ST_Emitter2		=  4	UMETA(DisplayName="Emitter 2"),
	ST_Emitter3		=  5	UMETA(DisplayName="Emitter 3"),
	ST_Emitter4		=  6	UMETA(DisplayName="Emitter 4"),
	ST_Spec1		=  7	UMETA(DisplayName="Spec 1"),
	ST_Spec2		=  8	UMETA(DisplayName="Spec 2"),
	ST_Spec3		=  9	UMETA(DisplayName="Spec 3"),
	ST_Spec4		= 10	UMETA(DisplayName="Spec 4")
};

// Returns the Score Category as Text.
inline FString operator ~(ESoundActorType SoundType)
{
	switch (SoundType)
	{
		case ESoundActorType::ST_Background1:	return (TEXT("Background 1"));
		case ESoundActorType::ST_Background2:	return (TEXT("Background 2"));
		case ESoundActorType::ST_Emitter1:		return (TEXT("Emitter 1"));
		case ESoundActorType::ST_Emitter2:		return (TEXT("Emitter 2"));
		case ESoundActorType::ST_Emitter3:		return (TEXT("Emitter 3"));
		case ESoundActorType::ST_Emitter4:		return (TEXT("Emitter 4"));
		case ESoundActorType::ST_Spec1:			return (TEXT("Spec 1"));
		case ESoundActorType::ST_Spec2:			return (TEXT("Spec 2"));
		case ESoundActorType::ST_Spec3:			return (TEXT("Spec 3"));
		case ESoundActorType::ST_Spec4:			return (TEXT("Spec 4"));
		default: 								return (TEXT("Invalid sound pawn type."));
	}
}

// Returns true if the value is SPT_Unspecified.
inline uint8 operator *(ESoundActorType SoundType)
{
	switch (SoundType)
	{
		case ESoundActorType::ST_Background1:	return 0;
		case ESoundActorType::ST_Background2:	return 1;

		case ESoundActorType::ST_Emitter1:		return 0;
		case ESoundActorType::ST_Emitter2:		return 1;
		case ESoundActorType::ST_Emitter3:		return 2;
		case ESoundActorType::ST_Emitter4:		return 3;

		case ESoundActorType::ST_Spec1:			return 0;
		case ESoundActorType::ST_Spec2:			return 1;
		case ESoundActorType::ST_Spec3:			return 2;
		case ESoundActorType::ST_Spec4:			return 3;

		default: 								return NULL; // 0
	}
}

// Returns true if the value is SPT_Unspecified.
inline bool operator !(ESoundActorType SoundType)
{
	return !((bool)SoundType); 
}