// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"
#include "MyFirstFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CPPINTRO_API UMyFirstFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static void WriteExcelFile(const FString FileName, const FString ExcelFile);
	static FString ReadFile(const FString FileName);
};
