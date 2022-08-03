// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 * 保存游戏：当按下Q键时保存关卡进度
 */
UCLASS(BlueprintType)
class TEMPPROJECT01_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	/* 已通过的关卡数 */
	UPROPERTY(BlueprintReadWrite)
	int32 SavedLevelCount;

	/* 保存进度的关卡名 */
	UPROPERTY(BlueprintReadWrite)
	FName SavedLevelName;

	/* 保存进度的分数 */
	UPROPERTY(BlueprintReadWrite)
	int32 SavedScore;

	/* 当前玩家已获得的buff等级 */
	UPROPERTY(BlueprintReadWrite)
	int32 SavedBuffLevel;
};
