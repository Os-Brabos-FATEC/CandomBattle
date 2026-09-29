// Fill out your copyright notice in the Description page of Project Settings.


#include "CandomBattleGameInstance.h"

#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"

void UCandomBattleGameInstance::Init()
{
	Super::Init();
	if (UGameUserSettings* Settings = GEngine->GetGameUserSettings())
	{
		// Settings->SetVSyncEnabled(true);
		// Settings->SetFrameRateLimit(60.f);
		// Settings->ApplySettings(false);
	}
}