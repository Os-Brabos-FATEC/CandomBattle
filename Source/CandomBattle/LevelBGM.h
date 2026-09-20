// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Sound/SoundBase.h"

#include "LevelBGM.generated.h"

UCLASS()
class CANDOMBATTLE_API ALevelBGM : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* LevelBGMComp;
	
	// Sets default values for this actor's properties
	ALevelBGM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
