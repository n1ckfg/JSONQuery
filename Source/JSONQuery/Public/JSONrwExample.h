// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JSONrw.h"
#include "JSONrwExample.generated.h"

UCLASS()
class JSONQUERY_API AJSONrwExample : public AJSONrw
{
	GENERATED_BODY()
	
public:	
	AJSONrwExample();

protected:
	virtual void BeginPlay() override;

};
