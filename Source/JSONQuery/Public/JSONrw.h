#pragma once

#include "JSONQuery.h"

#include "JSONrw.generated.h"

UCLASS()
class JSONQUERY_API AJSONrw : public AActor 
{
	GENERATED_BODY()

	public:
		AJSONrw();

		TSharedPtr<FJsonObject> JsonParsed;

	protected:
		virtual void BeginPlay() override;

};