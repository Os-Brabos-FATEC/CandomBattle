// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CameraBounds.h"

#include "Camera/CameraModifier.h"
#include "CameraBoundsModifier.generated.h"

/**
 * 
 */
UCLASS()
class CANDOMBATTLE_API UCameraBoundsModifier : public UCameraModifier
{
	GENERATED_BODY()
public:	
	virtual void AddedToCamera(APlayerCameraManager* Camera) override;
	virtual bool ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV) override;
};
