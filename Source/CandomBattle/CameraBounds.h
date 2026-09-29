// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraBounds.generated.h"

UCLASS()
class CANDOMBATTLE_API ACameraBounds : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBox2D CameraBoundsParam = FBox2D(ForceInitToZero);
	
	// Sets default values for this actor's properties
	ACameraBounds();
	
	FBox2D GetCameraBounds();
	
};
