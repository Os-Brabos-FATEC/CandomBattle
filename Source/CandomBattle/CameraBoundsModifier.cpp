// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBoundsModifier.h"

void UCameraBoundsModifier::AddedToCamera(APlayerCameraManager* Camera)
{
	
}

bool UCameraBoundsModifier::ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV)
{
	Super::ModifyCamera(DeltaTime, InOutPOV);
	
	if (InOutPOV.Location.X > CameraBoundsParam.Min)
	InOutPOV.Location
	
	return true;
}