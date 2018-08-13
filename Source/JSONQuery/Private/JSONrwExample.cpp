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
	
	TArray<TSharedPtr<FJsonValue>> objs = JsonParsed->GetArrayField("objects");

	if (objs.Num() > 0)
	{
		UE_LOG(JSONQueryLog, Warning, TEXT("Found array with objects: %i"), objs.Num());
	}
	else
	{
		UE_LOG(JSONQueryLog, Warning, TEXT("Did not find array."));
	}

	for (int i = 0; i < objs.Num(); i++)
	{
		TSharedPtr <FJsonObject> obj = objs[i]->AsObject();
		FString typeVal = obj->GetStringField("type");
		UE_LOG(JSONQueryLog, Warning, TEXT("FOUND TYPE: %s"), *typeVal);
	}

	/*
	int exI = JsonParsed->GetIntegerField("ExampleInt");
	bool exB = JsonParsed->GetBoolField("ExampleBool");
	FString exS = JsonParsed->GetStringField("ExampleString");
	float exF = JsonParsed->GetNumberField("ExampleFloat");
	double exD = JsonParsed->GetNumberField("ExampleDouble");
	*/
}

