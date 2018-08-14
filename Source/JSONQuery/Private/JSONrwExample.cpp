// Fill out your copyright notice in the Description page of Project Settings.

#include "JSONrwExample.h"

// Sets default values
AJSONrwExample::AJSONrwExample()
{
	//
}

// Called when the game starts or when spawned
void AJSONrwExample::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<TSharedPtr<FJsonValue>> jsonNodes = JsonParsed->GetArrayField("objects");

	if (jsonNodes.Num() > 0)
	{
		UE_LOG(JSONQueryLog, Warning, TEXT("Found array with objects: %i"), jsonNodes.Num());
	}
	else
	{
		UE_LOG(JSONQueryLog, Warning, TEXT("Did not find array."));
	}

	for (int i = 0; i < jsonNodes.Num(); i++)
	{
		objects.Add(createObject(jsonNodes[i]->AsObject()));
	}

	/*
	TArray<TSharedPtr<FJsonValue>> exArray = JsonParsed->GetArrayField("ExampleArray");
	TSharedPtr<FJsonObject> exArrayMember = exArray[0]->AsObject();
	int exI = JsonParsed->GetIntegerField("ExampleInt");
	bool exB = JsonParsed->GetBoolField("ExampleBool");
	FString exS = JsonParsed->GetStringField("ExampleString");
	float exF = JsonParsed->GetNumberField("ExampleFloat");
	double exD = JsonParsed->GetNumberField("ExampleDouble");
	*/
}

FExampleObj AJSONrwExample::createObject(TSharedPtr<FJsonObject> jsonNode)
{
	FExampleObj newObject = FExampleObj();

	newObject.type = jsonNode->GetStringField("type");
	newObject.position = getFVector(jsonNode->GetArrayField("position"));
	newObject.rotation = getFVector(jsonNode->GetArrayField("rotation"));
	newObject.scale = getFVector(jsonNode->GetArrayField("scale"));

	UE_LOG(JSONQueryLog, Warning, TEXT("FOUND TYPE: %s"), *newObject.type);

	return newObject;
}

void AJSONrwExample::createMesh(FString MeshName)
{
	UStaticMesh *MeshAsset = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *MeshName));
	Mesh->SetStaticMesh(MeshAsset);
}

void AJSONrwExample::spawnCube()
{
	UWorld * const World = GetWorld();
	if (World)
	{
		static ConstructorHelpers::FClassFinder<AActor> classFinder(TEXT("/Plugins/JSONQuery/Content/Examples/Blueprints/BP_TestCube.BP_TestCube"));
		if (classFinder.Class != nullptr)
		{
			World->SpawnActor<AActor>(classFinder.Class);
		}
	}
}