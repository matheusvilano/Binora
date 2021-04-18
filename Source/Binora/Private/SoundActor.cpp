// This work by Matheus Vilano is licensed under Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License. To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/4.0/


#include "SoundActor.h"

// Sets default values
ASoundActor::ASoundActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoundActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASoundActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

