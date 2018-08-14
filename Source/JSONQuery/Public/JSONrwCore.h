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

		FVector getFVector(TArray<TSharedPtr<FJsonValue>> jsonNode);

		TSharedPtr<FJsonObject> JsonParsed;

	protected:
		virtual void BeginPlay() override;

};