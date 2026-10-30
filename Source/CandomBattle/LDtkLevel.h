// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LDtkLevel.generated.h"

class UPaperTileMapComponent;
class UPaperTileSet;
class UBoxComponent;
class UTexture2D;
class FJsonObject;

UCLASS()
class CANDOMBATTLE_API ALDtkLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALDtkLevel();
	
	UPROPERTY(EditAnywhere, Category = "LDtk", meta = (FilePathFilter="json", RelativeToGameDir))
	FFilePath LDtkFile;
	
	UPROPERTY(EditAnywhere, Category = "LDtk")
	TObjectPtr<UTexture2D> TilesetTexture;
	
	UPROPERTY(EditAnywhere, Category = "LDtk")
	float PixelsPerUnrealUnit = 0.5;
	
	UPROPERTY(EditAnywhere, Category = "LDtk")
	float CollisionThickness = 64.f;
	
	UFUNCTION(CallInEditor, Category = "LDtk")
	void ImportLDtk();

protected:
	UPROPERTY(VisibleAnywhere, Category = "LDtk")
	TObjectPtr<UPaperTileMapComponent> TileMapComp;
	
	UPROPERTY()
	TObjectPtr<UPaperTileSet> GeneratedTileSet;
	
	UPROPERTY()
	TArray<TObjectPtr<UBoxComponent>> GeneratedColliders;

private:	
	bool LoadJson(TSharedPtr<FJsonObject>& OutRoot) const;
	UPaperTileSet* BuildTileSet(const TSharedPtr<FJsonObject>& TilesetDef);
	void BuildTiles(const TSharedPtr<FJsonObject>& Layer, UPaperTileSet* TileSet);
	void BuildCollision(const TSharedPtr<FJsonObject>& Layer);
	void ClearGenerated();
};
