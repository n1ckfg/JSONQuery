// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JSONrwCore.h"

#include "JSONrwExample.generated.h"

USTRUCT()
struct FExampleObj 
{
	GENERATED_BODY()

	FString type;
	FVector position;
	FVector rotation;
	FVector scale;

	FExampleObj()  
	{
		type = "none";
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
		void createMesh(FString MeshName);
		void spawnCube();
		FExampleObj createObject(TSharedPtr<FJsonObject> jsonNode);

		TArray<FExampleObj> objects;
		UStaticMeshComponent *Mesh;

	protected:
		virtual void BeginPlay() override;

};
