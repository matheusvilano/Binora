// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "FMODAudioComponent.h"
#include "FMODEvent.h"
#include "Materials/MaterialInterface.h"
#include "Math/Color.h"
#include "SoundActorType.h"

#include "SoundActor.generated.h"

// Forward declaration
struct FColor;
class UFMODAudioComponent;
class UFMODEvent;
class UMaterialInterface;
class USphereCollision;

UCLASS()
class BINORA_API ASoundActor : public AActor
{
	GENERATED_BODY()

	#pragma region Constructors

		public:	

			// Sets default values for this actor's properties
			ASoundActor();

			// Construction script
			virtual void OnConstruction(const FTransform& Transform) override;

	#pragma endregion

	#pragma region Sound

		protected:

			// This component will handle playing and stopping sounds.
			UPROPERTY(BlueprintReadOnly, DisplayName="FMOD Audio Component")
			UFMODAudioComponent* FMODAudioComponent = nullptr;

			UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Sound Pawn|Sound", DisplayName="FMOD Event")
			UFMODEvent* FMODEvent = nullptr;

			// What type of SoundPawn this is.
			UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Sound Pawn|Sound", DisplayName="Type")
			ESoundActorType SoundType = ESoundActorType::ST_Unspecified;

	#pragma endregion

	#pragma region Score

		protected:

			// The inner sphere component.
			UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="Inner Sphere Component")
			USphereComponent* InnerSphereComponent = nullptr;

			// The middle sphere component.
			UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="Middle Sphere Component")
			USphereComponent* MiddleSphereComponent = nullptr;

			// The outer sphere component.
			UPROPERTY(BlueprintReadOnly, VisibleAnywhere, DisplayName="Outer Sphere Component")
			USphereComponent* OuterSphereComponent = nullptr;

			// The radius of the inner Sphere. It indirectly affects gameplay difficulty: the smaller the radius, the harder the game. Avoid changing.
			UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Sound Pawn|Sphere", DisplayName="Inner Radius", Meta=(ClampMin=10.0f, ClampMax=500.0f))
			float InnerSphereRadius = 15.0f;

			// The radius of the middle Sphere. It indirectly affects gameplay difficulty: the smaller the radius, the harder the game. Avoid changing.
			UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Sound Pawn|Sphere", DisplayName="Middle Radius", Meta=(ClampMin=20.0f, ClampMax=500.0f))
			float MiddleSphereRadius = 50.0f;

			// The radius of the outer Sphere. It indirectly affects gameplay difficulty: the smaller the radius, the harder the game. Avoid changing.
			UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Sound Pawn|Sphere", DisplayName="Outer Radius", Meta=(ClampMin=40.0f, ClampMax=500.0f))
			float OuterSphereRadius = 100.0f;

	#pragma endregion

	#pragma region Design

		protected:

			// The optional reference-Mesh material. It is recommended you use simple colours for reference only, as the Mesh will be invisible in-game.
			UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category="Sound Pawn|Sphere", DisplayName="Outline Colour")
			FColor SphereColour = FColor::White;

	#pragma endregion

	#pragma region Inherited

		protected:
			
			// Called when the game starts or when spawned
			virtual void BeginPlay() override;

	#pragma endregion

};
