// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterData.h"

FMonsterInfo UMonsterData::FindMonsterDataForMonsterDataName(FName MonsterName)
{
	for (const FMonsterInfo& Data : MonsterData)
	{
		if (Data.MonsterName == MonsterName)
		{
			return Data;
		}
	}
	return FMonsterInfo();
}