#pragma once

#include "CoreMinimal.h"

///List of all enums in the app

UENUM(BlueprintType)
enum class EStatusToPlayer : uint8
{
	STP_Friendly	UMETA(DisplayName = "Friendly"),
	STP_Neutral		UMETA(DisplayName = "Neutral"),
	STP_Hostile		UMETA(DisplayName = "Hostile"),
	STP_None		UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	RT_Wood	UMETA(DisplayName = "Wood")
	//To Add
};

UENUM(BlueprintType)
enum class ENextClickFlag : uint8
{
	NCF_Move	UMETA(DisplayName = "MoveNext"),
	NCF_Attack	UMETA(DisplayName = "AttackNext"),
	NCF_Select	UMETA(DisplayName = "SelectNext"),
	NCF_Esc		UMETA(DisplayName = "NoneNext"),
	NCF_Gather	UMETA(DisplayName = "GatherNext")
	//to add
};