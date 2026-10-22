// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraModifier.h"

#include "PlayerCameraModifier.generated.h"

/**
 * 
 */
UCLASS()
class CANDOMBATTLE_API UPlayerCameraModifier : public UCameraModifier
{
	GENERATED_BODY()
public:
	FBox2D CameraBoundsParam;
	float PixelsPerUU = .5f;
	
	virtual void AddedToCamera(APlayerCameraManager* Camera) override;
	virtual bool ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV) override;
};
