// Fill out your copyright notice in the Description page of Project Settings.

#include "LDtkLevel.h"

#include "PaperTileMapComponent.h"
#include "PaperTileMap.h"
#include "PaperTileSet.h"
#include "PaperTileLayer.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"


// Sets default values
ALDtkLevel::ALDtkLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TileMapComp = CreateDefaultSubobject<UPaperTileMapComponent>(TEXT("TileMap"));
	RootComponent = TileMapComp;

}

bool ALDtkLevel::LoadJson(TSharedPtr<FJsonObject>& OutRoot) const
{
	const FString Path = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir(), LDtkFile.FilePath);
	
	FString Text;
	if (!FFileHelper::LoadFileToString(Text, *Path))
	{
		UE_LOG(LogTemp, Error, TEXT("LDtk: can't read %s"), *Path);
		return false;
	}
	
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Text);
	if (!FJsonSerializer::Deserialize(Reader, OutRoot) || !OutRoot.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("LDtk: %s is not valid JSON"), *Path);
		return false;
	}
	
	const TSharedPtr<FJsonObject>* Header = nullptr;
	if (!OutRoot->TryGetObjectField(TEXT("__header__"), Header) || (*Header)->GetStringField(TEXT("fileType")) != TEXT("LDtk Project JSON"))
	{
		UE_LOG(LogTemp, Error, TEXT("LDtk: %s is not an LDtk project"), *Path);
		return false;
	}
	return true;
}

UPaperTileSet* ALDtkLevel::BuildTileSet(const TSharedPtr<FJsonObject>& TilesetDef)
{
	const int32 Grid = TilesetDef->GetIntegerField(TEXT("tileGridSize"));
	const int32 Spacing = TilesetDef->GetIntegerField(TEXT("spacing"));
	const int32 Padding = TilesetDef->GetIntegerField(TEXT("padding"));
	
	GeneratedTileSet = NewObject<UPaperTileSet>(this, NAME_None, RF_Transactional);
	GeneratedTileSet->SetTileSheetTexture(TilesetTexture);
	GeneratedTileSet->SetTileSize(FIntPoint(Grid, Grid));
	GeneratedTileSet->SetPerTileSpacing(FIntPoint(Spacing, Spacing));
	GeneratedTileSet->SetMargin(FIntMargin(Padding));
	return GeneratedTileSet;
}

void ALDtkLevel::BuildTiles(const TSharedPtr<FJsonObject>& Layer, UPaperTileSet* TileSet)
{
	const int32 CWid = Layer->GetIntegerField(TEXT("__cWid"));
	const int32 CHei = Layer->GetIntegerField(TEXT("__cHei"));
	const int32 Grid = Layer->GetIntegerField(TEXT("__gridSize"));
	
	TileMapComp->CreateNewTileMap(CWid, CHei, Grid, Grid, PixelsPerUnrealUnit, true);
	TileMapComp->AddNewLayer();
	
	TArray<uint8> Stack;
	Stack.SetNumZeroed(CWid * CHei);
	
	auto PlaceTiles = [&](const TArray<TSharedPtr<FJsonValue>>& Tiles)
	{
		for (const TSharedPtr<FJsonValue>& Value : Tiles)
		{
			const TSharedPtr<FJsonObject> Tile = Value->AsObject();
			const TArray<TSharedPtr<FJsonValue>>& Px = Tile->GetArrayField(TEXT("px"));
			const int32 X = (int32)Px[0]->AsNumber() / Grid;
			const int32 Y = (int32)Px[1]->AsNumber() / Grid;
			if (X < 0 || X >= CWid || Y < 0 || Y >= CHei)
			{
				continue;
			}
			
			const int32 Flips = Tile->GetIntegerField(TEXT("f"));
			
			FPaperTileInfo Info;
			Info.TileSet = TileSet;
			Info.PackedTileIndex = Tile->GetIntegerField(TEXT("t"));
			Info.SetFlagValue(EPaperTileFlags::FlipHorizontal, (Flips & 1) != 0);
			Info.SetFlagValue(EPaperTileFlags::FlipVertical, (Flips & 2) != 0);
			
			uint8& Count = Stack[Y *CWid + X];
			if (Count < 2)
			{
				TileMapComp->SetTile(X, Y, 1 - Count, Info);
				++Count;
			}
		}
	};
	PlaceTiles(Layer->GetArrayField(TEXT("autoLayerTiles")));
	PlaceTiles(Layer->GetArrayField(TEXT("gridTiles")));
}

void ALDtkLevel::BuildCollision(const TSharedPtr<FJsonObject>& Layer)
{
	const int32 CWid = Layer->GetIntegerField(TEXT("__cWid"));
	const int32 CHei = Layer->GetIntegerField(TEXT("__cHei"));
	const int32 Grid = Layer->GetIntegerField(TEXT("__gridSize"));
	const float TileUU = Grid / PixelsPerUnrealUnit;
	
	const TArray <TSharedPtr<FJsonValue>>& Csv = Layer->GetArrayField(TEXT("intGridCsv"));
	TArray<bool> Solid;
	Solid.SetNumZeroed(CWid * CHei);
	for (int32 I = 0; I < Csv.Num() && I < Solid.Num(); ++I)
	{
		Solid[I] = Csv[I]->AsNumber() != 0;
	}
	
	for (int32 Y = 0; Y < CHei; ++Y)
	{
		for (int32 X = 0; X < CWid; ++X)
		{
			if (!Solid[Y * CWid + X])
			{
				continue;
			}
			
			int32 W = 1;
			while (X + W < CWid && Solid[Y * CWid + X + W])
			{
				++W;
			}
			
			auto RowIsSolid = [&](int32 Row)
			{
				for (int32 I = 0; I < W; ++I)
				{
					if (!Solid[Row * CWid + X + I])
					{
						return false;
					}
				}
				return true;
			};
			int32 H = 1;
			while (Y + H < CHei && RowIsSolid(Y + H))
			{
				++H;
			}
			
			for (int32 RY = Y; RY < Y + H; ++ RY)
			{
				for (int32 RX = X; RX < X + W; ++RX)
				{
					Solid[RY * CWid + RX] = false;
				}
			}
			
			const FVector A = TileMapComp->GetTileCenterPosition(X, Y);
			const FVector B = TileMapComp->GetTileCenterPosition(X + W - 1, Y + H - 1);
			
			UBoxComponent* Box = NewObject<UBoxComponent>(this, NAME_None, RF_Transactional);
			Box->SetupAttachment(TileMapComp);
			Box->SetRelativeLocation((A + B) * .5f);
			Box->SetBoxExtent(FVector(W * TileUU * .5f, CollisionThickness * .5f, H * TileUU * .5f));
			Box->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
			AddInstanceComponent(Box);
			Box->RegisterComponent();
			GeneratedColliders.Add(Box);
		}
	}
}

void ALDtkLevel::ImportLDtk()
{
	if (!TilesetTexture)
	{
		UE_LOG(LogTemp, Error, TEXT("LDtk: set TileSet Texture before importing"));
		return;
	}
	
	TSharedPtr<FJsonObject> Root;
	if (!LoadJson(Root))
	{
		return;
	}
	
	const TSharedPtr<FJsonObject> TilesetDef = Root->GetObjectField(TEXT("defs"))->GetArrayField(TEXT("tilesets"))[0]->AsObject();
	const TSharedPtr<FJsonObject> Level = Root->GetArrayField(TEXT("levels"))[0]->AsObject();
	const TSharedPtr<FJsonObject> Layer = Level->GetArrayField(TEXT("layerInstances"))[0]->AsObject();
	
	Modify();
	ClearGenerated();
	
	UPaperTileSet* TileSet = BuildTileSet(TilesetDef);
	BuildTiles(Layer, TileSet);
	if (Layer->GetStringField(TEXT("__type")) == TEXT("IntGrid"))
	{
		BuildCollision(Layer);
	}
	
	UE_LOG(LogTemp, Log, TEXT("LDtk: imported %d colliders"), GeneratedColliders.Num());
}

void ALDtkLevel::ClearGenerated()
{
	for (UBoxComponent* Box : GeneratedColliders)
	{
		if (Box)
		{
			RemoveInstanceComponent(Box);
			Box->DestroyComponent();
		}
	}
	GeneratedColliders.Reset();
}