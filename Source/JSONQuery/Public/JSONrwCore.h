#pragma once

#include "JSONQuery.h"

#include "JSONrwCore.generated.h"

UCLASS()
class JSONQUERY_API AJSONrwCore : public AActor 
{
	GENERATED_BODY()

	public:
		AJSONrwCore();

		UClass* findBlueprint(ConstructorHelpers::FObjectFinder<UBlueprint> finder);
		FVector vecFromJson(TArray<TSharedPtr<FJsonValue>> jsonNode); 
		FTransform transformFromJson(TArray<TSharedPtr<FJsonValue>> position, TArray<TSharedPtr<FJsonValue>> rotation, TArray<TSharedPtr<FJsonValue>> scale);
		FTransform transformFromVec(FVector rotation, FVector position, FVector scale);

		void findAllActors(UWorld* World, TArray<AActor*>& Out); 

		TSharedPtr<FJsonObject> JsonParsed;
		bool writeFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting = true);


	protected:
		virtual void BeginPlay() override;

};