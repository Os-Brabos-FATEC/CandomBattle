// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBounds.h"

// Sets default values
ACameraBounds::ACameraBounds()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

FBox2D ACameraBounds::GetCameraBounds()
{
	return CameraBoundsParam;
}
