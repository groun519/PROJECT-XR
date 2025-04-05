// Fill out your copyright notice in the Description page of Project Settings.


#include "P_XR/Data/WeaponData.h"

FWeaponInfo UWeaponData::FindWeaponForWeaponName(FName WeaponName)
{
	for (FWeaponInfo Data : WeaponData)
	{
		if (Data.WeaponName == WeaponName)
		{
			return Data;
		}
	}
	return FWeaponInfo();
}
