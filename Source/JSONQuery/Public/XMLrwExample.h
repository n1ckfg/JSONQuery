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
		
		pugi::xml_document XmlDoc;

		FString url = "Plugins/JSONQuery/Content/Examples/Xml/input.xml";

		TSubclassOf<class AActor> BP_TestSphere;

	protected:
		virtual void BeginPlay() override;
};
