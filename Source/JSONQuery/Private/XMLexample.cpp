// Fill out your copyright notice in the Description page of Project Settings.

#include "XMLexample.h"

AXMLexample::AXMLexample()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> finder_BP_TestSphere(TEXT("Blueprint'/JSONQuery/Examples/Blueprints/BP_TestSphere.BP_TestSphere'"));
	BP_TestSphere = findBlueprint(finder_BP_TestSphere);

	loadXml(url, XmlDoc);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *XmlDoc);
}

void AXMLexample::BeginPlay()
{
	Super::BeginPlay();

	float scaler = 1000.0;

	pugi::xml_node xmlMotionCapture = XmlDoc.child("MotionCapture");

	for (pugi::xml_node xmlFrame = xmlMotionCapture.child("MocapFrame"); xmlFrame; xmlFrame = xmlFrame.next_sibling("MocapFrame"))
	{
		pugi::xml_node xmlJoints = xmlFrame.child("Skeleton").child("Joints");

		pugi::xml_node xmlHead = xmlJoints.child("head");

		float x = xmlHead.attribute("x").as_float() * scaler;
		float y = xmlHead.attribute("y").as_float() * scaler;
		float z = xmlHead.attribute("z").as_float() * scaler;

		FVector p = FVector(x, y, z);

		Instantiate(BP_TestSphere, transformFromVec(FVector(0, 0, 0), p, FVector(1, 1, 1)));
	}

}
