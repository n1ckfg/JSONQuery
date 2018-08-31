// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JSONrwCore.h"

#include "XMLrwExample.generated.h"

UCLASS()
class JSONQUERY_API AXMLrwExample : public AJSONrwCore
{
	GENERATED_BODY()

	public:
		AXMLrwExample();

	protected:
		virtual void BeginPlay() override;
};
