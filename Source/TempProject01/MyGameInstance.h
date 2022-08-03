// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/* 
 * 游戏实例
 */
UCLASS(BlueprintType)
class TEMPPROJECT01_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	/* 当前游戏玩家的通过关卡数量 */
	UPROPERTY(BlueprintReadWrite)
	int32 PassedLevelCount;

	/* 当前游戏玩家的分数 */
	UPROPERTY(BlueprintReadWrite)
	int32 TotalScore;

	/* 当前玩家的buff等级，每级buff可为玩家增加10%的分数 */
	UPROPERTY(BlueprintReadWrite)
	int32 BuffLevel;

	/* 玩家分数增加
	* @param ObtainedScore - 玩家获得的分数
	*/
	UFUNCTION(BlueprintCallable)
	void ObtainScore(int32 ObtainedScore);

};
