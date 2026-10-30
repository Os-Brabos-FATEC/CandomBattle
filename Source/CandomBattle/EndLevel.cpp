// Fill out your copyright notice in the Description page of Project Settings.


#include "EndLevel.h"
#include "PlayerCharacter.h"
#include "CandomBattleGameMode.h"

// Sets default values
AEndLevel::AEndLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(BoxComponent);
	
	IgnoranceFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("IgnoranceFlipbook"));
	IgnoranceFlipbook->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEndLevel::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEndLevel::OnHitboxBeginOverlap);
	
}

// Called every frame
void AEndLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndLevel::OnHitboxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
	{
		Player->GameOver();
	}
}