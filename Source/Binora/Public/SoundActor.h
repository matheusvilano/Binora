// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FMODAudioComponent.h"
#include "FMODEvent.h"
#include "SoundActor.generated.h"

// Forward declaration
class UFMODAudioComponent;
class UFMODEvent;
class USphereCollision;

UCLASS()
class BINORA_API ASoundActor : public AActor
{
	GENERATED_BODY()

#pragma region Constructors

	public:	
		// Sets default values for this actor's properties
		ASoundActor();

#pragma endregion

#pragma region Sound

	protected:

		// This component will handle playing and stopping sounds.
		UPROPERTY(BlueprintReadOnly, DisplayName="FMOD Audio Component")
		UFMODAudioComponent* FMODAudioComponent = nullptr;

		UPROPERTY(BlueprintReadOnly, EditInstanceOnly, DisplayName="FMOD Event")
		UFMODEvent* FMODEvent = nullptr;

#pragma endregion

#pragma region Score

	protected:

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="Inner Sphere Component")
		USphereComponent InnerSphereComponent = nullptr;

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="Middle Sphere Component")
		USphereComponent MiddleSphereComponent = nullptr;

		UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="Outer Sphere Component")
		USphereComponent OuterSphereComponent = nullptr;

#pragma endregion

#pragma region Inherited

	protected:
		
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

#pragma endregion

};
