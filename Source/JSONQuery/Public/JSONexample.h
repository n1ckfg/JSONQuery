// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RwCore.h"

#include "JSONExample.generated.h"

USTRUCT()
struct FExampleObj 
{
	GENERATED_BODY()

	FString type;
	AActor* bp;
	FVector position;
	FVector rotation;
	FVector scale;

	FExampleObj()  
	{
		type = "none";
		bp = nullptr;
		position = FVector(0, 0, 0);
		rotation = FVector(0, 0, 0);
		scale = FVector(1, 1, 1);
	}
};

UCLASS()
class JSONQUERY_API AJSONExample : public ARwCore
{
	GENERATED_BODY()
	
	public:	
		AJSONExample();

		TSharedPtr<FJsonObject> JsonData;

		FExampleObj createObject(TSharedPtr<FJsonObject> jsonNode);
		TArray<FExampleObj> objects;
		void parseJson(TSharedPtr<FJsonObject> json);
		bool writeJson(FString SaveDirectory, FString FileName);

		FString url = "Plugins/JSONQuery/Content/Examples/Json/input.json";

		TSubclassOf<class AActor> BP_TestCube, BP_TestSphere;

	protected:
		virtual void BeginPlay() override;

};
