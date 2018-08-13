#include "JSONrw.h"

AJSONrw::AJSONrw() 
{
	PrimaryActorTick.bCanEverTick = true; 
}

void AJSONrw::BeginPlay() 
{ 
	Super::BeginPlay(); 

	UE_LOG(JSONQueryLog, Warning, TEXT("Begin loading JSON."));

	FString url = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + "Plugins/JSONQuery/Content/Example_BP/Json/input.json";
	UE_LOG(JSONQueryLog, Warning, TEXT("Loading File %s"), *url);

	FString JsonRaw;
	FFileHelper::LoadFileToString(JsonRaw, *url);
	UE_LOG(JSONQueryLog, Warning, TEXT("JSON Raw: %s"), *JsonRaw);

	TSharedPtr<FJsonObject> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonRaw);

	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed)) {
		UE_LOG(JSONQueryLog, Warning, TEXT("Parsing JSON."));
		
		TArray <TSharedPtr<FJsonValue>> objs = JsonParsed->GetArrayField("objects");
		for (int i = 0; i < objs.Num(); i++)
		{
			TSharedPtr <FJsonObject> obj = objs[i]->AsObject();
			FString typeVal = obj->GetStringField("type");
		}

		/*
		int exI = JsonParsed->GetIntegerField("ExampleInt");
		bool exB = JsonParsed->GetBoolField("ExampleBool");
		FString exS = JsonParsed->GetStringField("ExampleString");
		float exF = JsonParsed->GetNumberField("ExampleFloat");
		double exD = JsonParsed->GetNumberField("ExampleDouble");
		*/
	}
	else 
	{
		UE_LOG(JSONQueryLog, Error, TEXT("Error trying to parse JSON."));
	}
}
