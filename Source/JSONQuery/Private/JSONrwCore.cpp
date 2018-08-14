#include "JSONrwCore.h"

AJSONrwCore::AJSONrwCore()
{
	//
}

void AJSONrwCore::BeginPlay()
{ 
	Super::BeginPlay(); 

	UE_LOG(JSONQueryLog, Warning, TEXT("Begin loading JSON."));

	FString url = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + "Plugins/JSONQuery/Content/Examples/Json/input.json";
	UE_LOG(JSONQueryLog, Warning, TEXT("Loading File %s"), *url);

	FString JsonRaw;
	FFileHelper::LoadFileToString(JsonRaw, *url);
	UE_LOG(JSONQueryLog, Warning, TEXT("JSON Raw: %s"), *JsonRaw);

	//TSharedPtr<FJsonObject> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonRaw);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {
		UE_LOG(JSONQueryLog, Warning, TEXT("Deserialized JSON."));
	}
	else
	{
		UE_LOG(JSONQueryLog, Error, TEXT("Error trying to deserialize JSON."));
	}
}

FVector AJSONrwCore::getFVector(TArray<TSharedPtr<FJsonValue>> jsonNode)
{
	float x = jsonNode[0]->AsNumber();
	float y = jsonNode[1]->AsNumber();
	float z = jsonNode[2]->AsNumber();
	return FVector(x, y, z);
}

