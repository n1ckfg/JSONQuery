// Fill out your copyright notice in the Description page of Project Settings.

#include "JSONrwExample.h"

// Sets default values
AJSONrwExample::AJSONrwExample()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> finder_BP_TestCube(*formatBlueprintUrl("/Plugins/JSONQuery/Examples/Blueprints/BP_TestCube"));
	BP_TestCube = findBlueprint(finder_BP_TestCube);

	static ConstructorHelpers::FObjectFinder<UBlueprint> finder_BP_TestSphere(*formatBlueprintUrl("/Plugins/JSONQuery/Examples/Blueprints/BP_TestSphere"));
	BP_TestSphere = findBlueprint(finder_BP_TestSphere);
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

	for (int i = 0; i < jsonNodes.Num(); i++)
	{
		objects.Add(createObject(jsonNodes[i]->AsObject()));
	}

	TArray<AActor*> actors;
	findAllActors(GetWorld(), actors);
	
	TArray<FString> output;
	output.Add("eeee");
	output.Add("eaadafgaee");

	writeFile(FPaths::ProjectDir(), "output_cpp.json", FString::Join(output, _T("\n")), true);

	/*
	// more JSON examples:
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
	if (newObject.type == "cube")
	{
		newObject.bp = GetWorld()->SpawnActor(BP_TestCube);
	}
	else if (newObject.type == "sphere")
	{
		newObject.bp = GetWorld()->SpawnActor(BP_TestSphere);
	}
	newObject.position = vecFromJson(jsonNode->GetArrayField("position"));
	newObject.rotation = vecFromJson(jsonNode->GetArrayField("rotation"));
	newObject.scale = vecFromJson(jsonNode->GetArrayField("scale"));

	FTransform transform = makeTransform(newObject.position, newObject.rotation, newObject.scale);
	newObject.bp->SetActorTransform(transform);

	UE_LOG(JSONQueryLog, Warning, TEXT("FOUND TYPE: %s"), *newObject.type);

	return newObject;
}

void AJSONrwExample::createMesh(FString MeshName)
{
	UStaticMesh *MeshAsset = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *MeshName));
	Mesh->SetStaticMesh(MeshAsset);
}



