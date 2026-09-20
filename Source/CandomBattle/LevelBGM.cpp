// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelBGM.h"

// Sets default values
ALevelBGM::ALevelBGM()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	LevelBGMComp = CreateDefaultSubobject<USoundBase>("LevelBGMComp");
}

// Called when the game starts or when spawned
void ALevelBGM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelBGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

