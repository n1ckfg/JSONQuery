#pragma once

#include "JSONQuery.h"

#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "EngineUtils.h"
#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "ConstructorHelpers.h"

#include "JSONrwCore.generated.h"

UCLASS()
class JSONQUERY_API AJSONrwCore : public AActor 
{
	GENERATED_BODY()

	public:
		AJSONrwCore();

		FString formatBlueprintUrl(FString url);
		UClass* findBlueprint(ConstructorHelpers::FObjectFinder<UBlueprint> finder);
		FVector getFVector(TArray<TSharedPtr<FJsonValue>> jsonNode);
		FTransform getFTransform(TArray<TSharedPtr<FJsonValue>> position, TArray<TSharedPtr<FJsonValue>> rotation, TArray<TSharedPtr<FJsonValue>> scale);
		FTransform getFTransform(FVector position, FVector rotation, FVector scale);

		TSharedPtr<FJsonObject> JsonParsed;

	protected:
		virtual void BeginPlay() override;

};