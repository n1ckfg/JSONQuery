// Fill out your copyright notice in the Description page of Project Settings.

#include "JSONrwExample.h"

// Sets default values
AJSONrwExample::AJSONrwExample()
{
	// Initializing Blueprint references has to happen in the constructor.
	BP_TestCube = findBlueprint("/Plugins/JSONQuery/Examples/Blueprints/BP_TestCube");
	BP_TestSphere = findBlueprint("/Plugins/JSONQuery/Examples/Blueprints/BP_TestSphere");
}

// Called when the game starts or when spawned
void AJSONrwExample::BeginPlay()
{
	Super::BeginPlay();
	
	testCube = GetWorld()->SpawnActor(BP_TestCube);
	testSphere = GetWorld()->SpawnActor(BP_TestSphere);

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

UClass* AJSONrwExample::findBlueprint(FString url)
{
	url = formatBlueprintUrl(url);

	static ConstructorHelpers::FObjectFinder<UBlueprint> finder(*url);
	if (finder.Object != NULL)
	{
		UE_LOG(JSONQueryLog, Warning, TEXT("Found Blueprint at %s"), *url);
		return (UClass*) finder.Object->GeneratedClass;
	}
	else
	{
		UE_LOG(JSONQueryLog, Warning, TEXT("Failed to find Blueprint at %s"), *url);
		return NULL;
	}
}

// This is needed because a valid Blueprint url is slightly different from your directory structure
FString AJSONrwExample::formatBlueprintUrl(FString url)
{
	TArray<FString> urlSplit;
	url.ParseIntoArray(urlSplit, _T("/"));
	if (urlSplit[0] == "Plugins")
	{
		urlSplit.RemoveAt(0);
	}
	else if (urlSplit[0] == "Content")
	{
		urlSplit[0] = "Game";
	}
	return "Blueprint'/" + FString::Join(urlSplit, _T("/")) + "." + urlSplit[urlSplit.Num() - 1] + "'";
}