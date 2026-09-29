// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraBoundsModifier.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/PlayerCameraManager.h"

#include "CameraBounds.h"

void UCameraBoundsModifier::AddedToCamera(APlayerCameraManager* Camera)
{
	Super::AddedToCamera(Camera);
	
	ACameraBounds* CameraBoundsActor = Cast<ACameraBounds>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraBounds::StaticClass()));
	
	if (CameraBoundsActor)
	{
		CameraBoundsParam = CameraBoundsActor->GetCameraBounds();
	}
}

bool UCameraBoundsModifier::ModifyCamera(float DeltaTime, FMinimalViewInfo& InOutPOV)
{
	Super::ModifyCamera(DeltaTime, InOutPOV);
	
	const float TargetArtWidth = InOutPOV.OrthoWidth * PixelsPerUU;
	
	int32 VX = 0, VY = 0;
	if (APlayerController* Controller = CameraOwner ? CameraOwner->GetOwningPlayerController() : nullptr)
		Controller->GetViewportSize(VX, VY);
	
	float UUPerScreenPx = 0.f;
	if (VX > 0 && VY > 0 && TargetArtWidth > 0.f)
	{
		const float ViewW = FMath::Min((float)VX, VY * InOutPOV.AspectRatio);
		const int32 Scale = FMath::Max(1, FMath::FloorToInt(ViewW / TargetArtWidth));
		InOutPOV.OrthoWidth = ViewW / (Scale * PixelsPerUU);
		UUPerScreenPx = 1.f / (Scale * PixelsPerUU);
	}
	
	const float HalfW = InOutPOV.OrthoWidth * .5f;
	const float HalfH = HalfW / InOutPOV.AspectRatio;
	
	const float MinX = CameraBoundsParam.Min.X + HalfW;
	const float MaxX = CameraBoundsParam.Max.X - HalfW;
	const float MinY = CameraBoundsParam.Min.Y + HalfH;
	const float MaxY = CameraBoundsParam.Max.Y - HalfH;
	
	bool bClampedX = false, bClampedZ = false;
	if (MinX < MaxX)
	{
		const double C = InOutPOV.Location.X;
		InOutPOV.Location.X = FMath::Clamp(C, (double)MinX, (double)MaxX);
		bClampedX = InOutPOV.Location.X != C;
	}
	if (MinY < MaxY)
	{
		const double C = InOutPOV.Location.Z;
		InOutPOV.Location.Z = FMath::Clamp(C, (double)MinY, (double)MaxY);
		bClampedZ = InOutPOV.Location.Z != C;
	}
	
	if (UUPerScreenPx > 0.f)
	{
		const AActor* Target = CameraOwner ? CameraOwner->GetViewTarget() : nullptr;
		const FVector Anchor = Target ? Target->GetActorLocation() : FVector::ZeroVector;
		
		const double AX = bClampedX ? 0.0 : Anchor.X;
		const double AZ = bClampedZ ? 0.0 : Anchor.Z;
		
		InOutPOV.Location.X = AX + FMath::GridSnap(InOutPOV.Location.X - AX, (double)UUPerScreenPx);
		InOutPOV.Location.Z = AZ + FMath::GridSnap(InOutPOV.Location.Z - AZ, (double)UUPerScreenPx);
	}
	
	return false;
}