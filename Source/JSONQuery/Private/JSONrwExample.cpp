// Fill out your copyright notice in the Description page of Project Settings.

#include "JSONrwExample.h"

// Sets default values
AJSONrwExample::AJSONrwExample()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> finder_BP_TestCube(TEXT("Blueprint'/JSONQuery/Examples/Blueprints/BP_TestCube.BP_TestCube'"));
	BP_TestCube = findBlueprint(finder_BP_TestCube);

	static ConstructorHelpers::FObjectFinder<UBlueprint> finder_BP_TestSphere(TEXT("Blueprint'/JSONQuery/Examples/Blueprints/BP_TestSphere.BP_TestSphere'"));
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

	writeJson(FPaths::ProjectDir(), "output_cpp.json");

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

bool AJSONrwExample::writeJson(FString SaveDirectory, FString FileName)
{
	TArray<FString> output;
	output.Add("{");
	output.Add("\t\"objects\": [");

	TArray<AActor*> actors;
	findAllActors(GetWorld(), actors);

	for (int i = 0; i < actors.Num(); i++)
	{
		//UE_LOG(JSONQueryLog, Warning, TEXT("Found actor %s"), *actors[i]->GetName());
		FString name = actors[i]->GetName();
		if (name.StartsWith("BP_TestCube") || name.StartsWith("BP_TestSphere"))
		{
			output.Add("\t\t{");

			FString type;
			if (name.StartsWith("BP_TestCube"))
			{
				type = "cube";
			}
			else if (name.StartsWith("BP_TestSphere"))
			{
				type = "sphere";
			}
			output.Add(FString() + "\t\t\t\"type\": \"" + type + "\",");

			FVector position = actors[i]->GetActorLocation();
			output.Add(FString() + "\t\t\t\"position\": [ " + FString::SanitizeFloat(position.X) + ", " + FString::SanitizeFloat(position.Y) + ", " + FString::SanitizeFloat(position.Z) + " ],");

			FVector rotation = actors[i]->GetActorRotation().Euler();
			output.Add(FString() + "\t\t\t\"rotation\": [ " + FString::SanitizeFloat(rotation.X) + ", " + FString::SanitizeFloat(rotation.Y) + ", " + FString::SanitizeFloat(rotation.Z) + " ],");

			FVector scale = actors[i]->GetActorScale3D();
			output.Add(FString() + "\t\t\t\"scale\": [ " + FString::SanitizeFloat(scale.X) + ", " + FString::SanitizeFloat(scale.Y) + ", " + FString::SanitizeFloat(scale.Z) + " ]");

			if (i == actors.Num() - 1)
			{
				output.Add("\t\t}");
			}
			else
			{
				output.Add("\t\t},");
			}
		}
	}

	output.Add("\t]");
	output.Add("}");

	return writeFile(SaveDirectory, FileName, FString::Join(output, _T("\n")), true);
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

	FTransform transform = transformFromVec(newObject.rotation, newObject.position, newObject.scale);
	newObject.bp->SetActorTransform(transform);

	UE_LOG(JSONQueryLog, Warning, TEXT("FOUND TYPE: %s"), *newObject.type);

	return newObject;
}



