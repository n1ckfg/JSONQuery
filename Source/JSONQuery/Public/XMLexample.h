// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "JSONrwCore.h"

#include "XMLexample.generated.h"

UCLASS()
class JSONQUERY_API AXMLexample : public AJSONrwCore
{
	GENERATED_BODY()

	public:
		AXMLexample();
		
		pugi::xml_document XmlDoc;

		FString url = "Plugins/JSONQuery/Content/Examples/Xml/input.xml";

		TSubclassOf<class AActor> BP_TestCube, BP_TestSphere;

	protected:
		virtual void BeginPlay() override;
};
