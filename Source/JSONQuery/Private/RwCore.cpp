#include "RwCore.h"

ARwCore::ARwCore()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void ARwCore::BeginPlay()
{ 
	Super::BeginPlay(); 
	//SetActorTickEnabled(true);
}

TSharedPtr<FJsonObject> ARwCore::loadJson(FString url)
{
	TSharedPtr<FJsonObject> JsonData;

	url = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + url;

	UE_LOG(JSONQueryLog, Warning, TEXT("Loading File %s"), *url);

	FString JsonRaw;
	FFileHelper::LoadFileToString(JsonRaw, *url);
	UE_LOG(JSONQueryLog, Warning, TEXT("JSON Raw: %s"), *JsonRaw);

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonRaw);

	if (FJsonSerializer::Deserialize(JsonReader, JsonData)) {
		UE_LOG(JSONQueryLog, Warning, TEXT("Deserialized JSON."));
	}
	else
	{
		UE_LOG(JSONQueryLog, Error, TEXT("Error trying to deserialize JSON."));
	}

	return JsonData;
}

bool ARwCore::loadXml(FString url, pugi::xml_document& XmlData)
{
	url = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()) + url;
	pugi::xml_parse_result res = XmlData.load_file(toString(url).c_str());
	if (!res)
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::string ARwCore::toString(FString s)
{
	return std::string(TCHAR_TO_UTF8(*s));
}

UClass* ARwCore::findBlueprint(ConstructorHelpers::FObjectFinder<UBlueprint> finder)
{
	FString url = finder.Object->GetPathName();
	UE_LOG(JSONQueryLog, Warning, TEXT("Found Blueprint at url: %s"), *url);
	return (UClass*)finder.Object->GeneratedClass;
}

FVector ARwCore::vecFromJson(TArray<TSharedPtr<FJsonValue>> jsonNode)
{	
	float x = jsonNode[0]->AsNumber();
	float y = jsonNode[1]->AsNumber();
	float z = jsonNode[2]->AsNumber();
	return FVector(x, y, z);
}

FTransform ARwCore::transformFromJson(TArray<TSharedPtr<FJsonValue>> rotation, TArray<TSharedPtr<FJsonValue>> position, TArray<TSharedPtr<FJsonValue>> scale)
{
	FVector rot = vecFromJson(rotation);
	return FTransform(UKismetMathLibrary::MakeRotator(rot.X, rot.Y, rot.Z), vecFromJson(position), vecFromJson(scale));
}

FTransform ARwCore::transformFromVec(FVector rotation, FVector position, FVector scale)
{
	return FTransform(UKismetMathLibrary::MakeRotator(rotation.X, rotation.Y, rotation.Z), position, scale);
}

void ARwCore::findAllActors(UWorld* World, TArray<AActor*>& Out)
{
	for (TActorIterator<AActor> It(World, AActor::StaticClass()); It; ++It) 
	{
		AActor* Actor = Cast<AActor>(*It);
		if (Actor && !Actor->IsPendingKill())
		{
			Out.Add(Actor);
		}
	}
}

bool ARwCore::writeFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting)
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
		
AActor* ARwCore::Instantiate(TSubclassOf<class AActor> bp, FTransform transform)
{
	AActor *returns = GetWorld()->SpawnActor(bp);
	returns->SetActorTransform(transform);
	return returns;
}

