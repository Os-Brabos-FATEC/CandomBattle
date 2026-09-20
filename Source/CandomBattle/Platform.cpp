// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform.h"

#include "Math/UnitConversion.h"
#include "Splines/SplineMath.h"
#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlatform::APlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OrbitArm = CreateDefaultSubobject<USceneComponent>(FName("OrbitArm"));
	SetRootComponent(OrbitArm);

	ArrowComp = CreateEditorOnlyDefaultSubobject<UArrowComponent>(FName("ArrowComp"));
	if (ArrowComp)
		ArrowComp->SetupAttachment(RootComponent);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(FName("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->BodyInstance.DOFMode = EDOFMode::CustomPlane;
	BoxComp->BodyInstance.bLockXRotation = true;
	BoxComp->BodyInstance.bLockYRotation = true;
	BoxComp->BodyInstance.bLockYTranslation = true;
	BoxComp->BodyInstance.bLockZRotation = true;
	
	TriggerBoxComp = CreateDefaultSubobject<UBoxComponent>(FName("TriggerBoxComp"));
	TriggerBoxComp->SetupAttachment(BoxComp);

	FlipbookComp = CreateDefaultSubobject<UPaperFlipbookComponent>(FName("FlipbookComp"));
	FlipbookComp->SetupAttachment(BoxComp);

	MovementPath = CreateEditorOnlyDefaultSubobject<USplineComponent>(TEXT("MovementPath"));
	if (MovementPath)
	{
		MovementPath->SetupAttachment(RootComponent);
		MovementPath->SetRelativeLocation(FVector(0.f, 1.f, 0.f));
	}
	RotationRadius = CreateEditorOnlyDefaultSubobject<USphereComponent>(FName("RotationRadius"));
	if (RotationRadius)
		RotationRadius->SetupAttachment(RootComponent);

	InterpToMoveComp = CreateDefaultSubobject<UInterpToMovementComponent>(FName("InterpToMoveComp"));
	InterpToMoveComp->SetUpdatedComponent(RootComponent);

	RotatingMoveComp = CreateDefaultSubobject<URotatingMovementComponent>(FName("RotatingMoveComp"));
	RotatingMoveComp->SetUpdatedComponent(RootComponent);
}

void APlatform::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (MovementPath && InterpToMoveComp)
	{
		MovementPath->ClearSplinePoints(false);
		for (int32 i = 0; i < InterpToMoveComp->ControlPoints.Num(); ++i)
		{
			MovementPath->AddSplinePoint(InterpToMoveComp->ControlPoints[i].PositionControlPoint,
			                             InterpToMoveComp->ControlPoints[i].bPositionIsRelative
				                             ? ESplineCoordinateSpace::Local
				                             : ESplineCoordinateSpace::World, false);
			MovementPath->SetSplinePointType(i, ESplinePointType::Linear, false);
		}
		MovementPath->UpdateSpline();

		if (ActivateInterpFactor)
		{
			float Distance = MovementPath->GetSplineLength();
			float* InterpPeriod = &InterpToMoveComp->Duration;
			if (InterpAuthAttribute == EInterpAuthAttribute::InterpBasePeriod)
				InterpMovementSpeed = Distance / (InterpBasePeriod * InterpCycleFactor);
			if (InterpAuthAttribute == EInterpAuthAttribute::InterpMovementSpeed)
				InterpBasePeriod = Distance / (InterpMovementSpeed * InterpCycleFactor);
			*InterpPeriod = InterpBasePeriod * InterpCycleFactor;
		}

		if (RotationRadius)
		{
			const FVector Relloc = BoxComp->GetRelativeLocation();
			const double Radius = FMath::Sqrt(FMath::Square(Relloc.X) + FMath::Square(Relloc.Z));
			RotationRadius->SetSphereRadius(Radius);

			if (ActivateRotationFactor)
			{
				double* RotationPeriod = &RotatingMoveComp->RotationRate.Pitch;
				if (RotationAuthAttribute == ERotationAuthAttribute::RotationBasePeriod)
					RotationMovementSpeed = (2 * UE_DOUBLE_PI * Radius) / (RotationBasePeriod * RotationCycleFactor);
				if (RotationAuthAttribute == ERotationAuthAttribute::RotationMovementSpeed)
					RotationBasePeriod = (2 * UE_DOUBLE_PI * Radius) / (RotationMovementSpeed * RotationCycleFactor);
				*RotationPeriod = 360. / (RotationBasePeriod * RotationCycleFactor);
			}
		}
	}
}

// Called when the game starts or when spawned
void APlatform::BeginPlay()
{
	Super::BeginPlay();

	if (FallingPlatform)
	{
		FlipbookStartingPosition = FlipbookComp->GetRelativeLocation();
		BoxComp->SetNotifyRigidBodyCollision(true);
		BoxComp->OnComponentHit.AddDynamic(this, &APlatform::FallingPlatformEvent);
	}

	if (TouchToMove)
	{
		InterpToMoveComp->StopMovementImmediately();
		TriggerBoxComp->OnComponentBeginOverlap.AddDynamic(this, &APlatform::OnBoxBeginOverlap);
		TriggerBoxComp->OnComponentEndOverlap.AddDynamic(this, &APlatform::OnBoxEndOverlap);
	}
}

// Called every frame
void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (FallingPlatform)
	{
		TrembleElapsedTime = FMath::Fmod(TrembleElapsedTime + DeltaTime, (2 * UE_DOUBLE_PI) / TrembleSpeed);
		TremblingPlatformEffect();
	}
}

void APlatform::TremblingPlatformEffect()
{
	FlipbookComp->SetRelativeLocation(
		FlipbookStartingPosition + FVector(TrembleAmplitude * FMath::Cos(TrembleSpeed * TrembleElapsedTime), 0.f, 0.f));
}

void APlatform::FallingPlatformEvent(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                     FVector NormalImpulse, const FHitResult& Hit)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		GetWorldTimerManager().SetTimer(FallingPlatformTimer, this, &APlatform::FallingPlatformTimerEvent, 1.f, false,
		                                PlatformTimeToFall);
	}
}

void APlatform::FallingPlatformTimerEvent()
{
	BoxComp->SetSimulatePhysics(true);
	GetWorldTimerManager().SetTimer(FallingPlatformTimer, this, &APlatform::CheckPlatformOutOfCameraView, 1.f, true,
	                                1.f);
}

void APlatform::CheckPlatformOutOfCameraView()
{
	if (APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0))
	{
		FVector2D ScreenPosition;
		int32 ViewportSizeX, ViewportSizeY;
		Controller->GetViewportSize(ViewportSizeX, ViewportSizeY);
		bool bIsOnScreen = Controller->ProjectWorldLocationToScreen(BoxComp->GetComponentLocation(), ScreenPosition,
		                                                            false);

		if (bIsOnScreen == false || ScreenPosition.X < 0 || ScreenPosition.X > ViewportSizeX || ScreenPosition.Y < 0 ||
			ScreenPosition.Y > ViewportSizeY)
		{
			BoxComp->SetSimulatePhysics(false);
			FlipbookComp->SetHiddenInGame(true);
			BoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			BoxComp->AttachToComponent(OrbitArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			GetWorldTimerManager().ClearTimer(FallingPlatformTimer);
			GetWorldTimerManager().SetTimer(FallingPlatformTimer, this, &APlatform::RespawnPlatform, 1.f, false,
			                                PlatformTimeToRespawn);
		}
	}
}

void APlatform::RespawnPlatform()
{
	FlipbookComp->SetHiddenInGame(false);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void APlatform::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (GetWorldTimerManager().IsTimerActive(TouchPlatformReturnTimer))
		{
			GetWorldTimerManager().ClearTimer(TouchPlatformReturnTimer);
		}
		else
		{
			FTimerDelegate TimerDel = FTimerDelegate::CreateUObject(this, &APlatform::StartPlatform, OtherActor);
			GetWorldTimerManager().SetTimer(TouchPlatformStartTimer, TimerDel, .05f, true, .05f);
		}
	}
}

void APlatform::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (GetWorldTimerManager().IsTimerActive(TouchPlatformStartTimer))
		{
			GetWorldTimerManager().ClearTimer(TouchPlatformStartTimer);
		}
		else
		{
			GetWorldTimerManager().SetTimer(TouchPlatformReturnTimer, this, &APlatform::ReturnPlatform, PlatformTimeToReturn, false);
		}
	}
}

void APlatform::StartPlatform(AActor* OtherActor)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		if (UCharacterMovementComponent* MC = Player->GetCharacterMovement())
		{
			if (MC->MovementMode == MOVE_Walking && MC->CurrentFloor.HitResult.GetComponent() == BoxComp)
			{
				GetWorldTimerManager().ClearTimer(TouchPlatformStartTimer);
				float Direction = 1.f;
				InterpToMoveComp->RestartMovement(Direction);
			}
		}
	}
}

void APlatform::ReturnPlatform()
{
	float Direction = 0.f;
	InterpToMoveComp->RestartMovement(Direction);
}
