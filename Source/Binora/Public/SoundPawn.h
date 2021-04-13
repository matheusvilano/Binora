// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "FMODAudioComponent.h"
#include "GameFramework/Pawn.h"
#include "SoundPawn.generated.h"

// Forward declaration
class UFMODAudioComponent;
class USphereComponent;

UCLASS()
class BINORA_API ASoundPawn : public APawn
{
	GENERATED_BODY()

#pragma region Constructors

	public:

		// Sets default values for this pawn's properties
		ASoundPawn();

#pragma endregion

#pragma region Gameplay

	protected:

		// The sphere collider to be used when counting the score.
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, DisplayName="Sphere")
		USphereComponent* SphereComp = nullptr;

#pragma endregion

#pragma region Sound

	protected:

		// The FMOD component in charge of managing sound for this Pawn.
		UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, DisplayName="Sound")
		UFMODAudioComponent* FMODAudioComp = nullptr;

#pragma endregion

#pragma region Framework

	public:	

		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma endregion

};
