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

// This is needed because a valid Blueprint url is slightly different from your directory structure
FString AJSONrwCore::formatBlueprintUrl(FString url)
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

UClass* AJSONrwCore::findBlueprint(ConstructorHelpers::FObjectFinder<UBlueprint> finder)
{
	FString url = finder.Object->GetPathName();
	UE_LOG(JSONQueryLog, Warning, TEXT("Found Blueprint at url: %s"), *url);
	return (UClass*)finder.Object->GeneratedClass;
}

FVector AJSONrwCore::vecFromJson(TArray<TSharedPtr<FJsonValue>> jsonNode)
{	
	float x = jsonNode[0]->AsNumber();
	float y = jsonNode[1]->AsNumber();
	float z = jsonNode[2]->AsNumber();
	return FVector(x, y, z);
}

FTransform AJSONrwCore::transformFromJson(TArray<TSharedPtr<FJsonValue>> position, TArray<TSharedPtr<FJsonValue>> rotation, TArray<TSharedPtr<FJsonValue>> scale)
{
	return FTransform(vecFromJson(rotation).Rotation().Quaternion(), vecFromJson(position), vecFromJson(scale));
}

FTransform AJSONrwCore::makeTransform(FVector position, FVector rotation, FVector scale)
{
	return FTransform(rotation.Rotation().Quaternion(), position, scale);
}

FTransform AJSONrwCore::makeTransform(FVector position, FQuat rotation, FVector scale)
{
	return FTransform(rotation, position, scale);
}

template<typename T>
void AJSONrwCore::findAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<AActor> It(World, T::StaticClass()); It; ++It)
	{
		T* Actor = Cast<T>(*It);
		if (Actor && !Actor->IsPendingKill())
		{
			Out.Add(Actor);
		}
	}
}

template<typename T>
void AJSONrwCore::findAllObjects(TArray<T*>& OutArray)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByClass(T::StaticClass()->GetFName(), AssetData);
	for (int i = 0; i < AssetData.Num(); i++) {
		T* Object = Cast<T>(AssetData[i].GetAsset());
		OutArray.Add(Object);
	}
}

bool AJSONrwCore::writeFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (SaveDirectory.Len() > 0)
	{
		FPaths::NormalizeDirectoryName(SaveDirectory);
		FPaths::NormalizeFilename(FileName);

		if (!PlatformFile.DirectoryExists(*SaveDirectory))
		{
			PlatformFile.CreateDirectory(*SaveDirectory);
			if (!PlatformFile.DirectoryExists(*SaveDirectory))
			{
				return false; // Failed to create the directory.
			}
		}

		SaveDirectory += "/" + FileName;
	}
	else
	{
		SaveDirectory = FPaths::ProjectDir() + "/" + FileName;
	}


	if (!AllowOverWriting)
	{
		if (PlatformFile.FileExists(*SaveDirectory))
		{
			return false; // Won't overwrite the file.
		}
	}

	return FFileHelper::SaveStringToFile(SaveText, *SaveDirectory);
}
