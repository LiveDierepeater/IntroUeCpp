// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstFunctionLibrary.h"

void UMyFirstFunctionLibrary::WriteExcelFile(FString FileName, FString ExcelFile)
{
	const FString Path = FPaths::ProjectSavedDir() + "ExcelFiles/" + FileName;
	FFileHelper::SaveStringToFile(ExcelFile, *Path);
}

FString UMyFirstFunctionLibrary::ReadFile(FString FileName)
{
	FString LoadFile;
	const FString Path = FPaths::ProjectSavedDir() + "ExcelFiles/" + FileName;
	FFileHelper::LoadFileToString(OUT LoadFile, *Path);
	return LoadFile;
}
