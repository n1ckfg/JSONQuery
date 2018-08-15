// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JSONrwCore.h"

#include "JSONrwExample.generated.h"

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
class JSONQUERY_API AJSONrwExample : public AJSONrwCore
{
	GENERATED_BODY()
	
	public:	
		AJSONrwExample();

		FExampleObj createObject(TSharedPtr<FJsonObject> jsonNode);
		TArray<FExampleObj> objects;
		bool writeJson(FString SaveDirectory, FString FileName);

		TSubclassOf<class AActor> BP_TestCube, BP_TestSphere;

		void createMesh(FString MeshName);
		UStaticMeshComponent *Mesh;

	protected:
		virtual void BeginPlay() override;

};
