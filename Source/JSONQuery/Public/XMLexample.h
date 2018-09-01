// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RwCore.h"

#include "XMLExample.generated.h"

UCLASS()
class JSONQUERY_API AXMLExample : public ARwCore
{
	GENERATED_BODY()

	public:
		AXMLExample();
		
		pugi::xml_document XmlData;

		void parseXml(pugi::xml_document &xml);

		FString url = "Plugins/JSONQuery/Content/Examples/Xml/input.xml";

		TSubclassOf<class AActor> BP_TestCube, BP_TestSphere;

	protected:
		virtual void BeginPlay() override;
};
