#pragma once

#include "JSONQuery.h"

#include "JSONrwCore.generated.h"

UCLASS()
class JSONQUERY_API AJSONrwCore : public AActor 
{
	GENERATED_BODY()

	public:
		AJSONrwCore();

		// utilities
		UClass* findBlueprint(ConstructorHelpers::FObjectFinder<UBlueprint> finder);
		FTransform transformFromVec(FVector rotation, FVector position, FVector scale);
		bool writeFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting = true);
		void findAllActors(UWorld* World, TArray<AActor*>& Out); 
		AActor* Instantiate(TSubclassOf<class AActor> bp, FTransform transform);
		std::string toString(FString s);

		// json
		TSharedPtr<FJsonObject> loadJson(FString url);
		FVector vecFromJson(TArray<TSharedPtr<FJsonValue>> jsonNode);
		FTransform transformFromJson(TArray<TSharedPtr<FJsonValue>> position, TArray<TSharedPtr<FJsonValue>> rotation, TArray<TSharedPtr<FJsonValue>> scale);

		// xml
		bool loadXml(FString url, pugi::xml_document& XmlData);

	protected:
		virtual void BeginPlay() override;
		//virtual void Tick(float DeltaTime) override;

};