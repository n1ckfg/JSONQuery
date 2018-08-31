// Fill out your copyright notice in the Description page of Project Settings.

#include "XMLexample.h"

AXMLexample::AXMLexample()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> finder_BP_TestCube(TEXT("Blueprint'/JSONQuery/Examples/Blueprints/BP_TestCube.BP_TestCube'"));
	BP_TestCube = findBlueprint(finder_BP_TestCube);

	static ConstructorHelpers::FObjectFinder<UBlueprint> finder_BP_TestSphere(TEXT("Blueprint'/JSONQuery/Examples/Blueprints/BP_TestSphere.BP_TestSphere'"));
	BP_TestSphere = findBlueprint(finder_BP_TestSphere);

	loadXml(url, XmlDoc);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *XmlDoc);
}

void AXMLexample::BeginPlay()
{
	Super::BeginPlay();

	float pos_scaler = 500.0;
	FVector pos_offset = FVector(0, 0, 500);

	float bp_scaler = 0.2;

	pugi::xml_node xmlMotionCapture = XmlDoc.child("MotionCapture");

	for (pugi::xml_node xmlFrame = xmlMotionCapture.first_child(); xmlFrame; xmlFrame = xmlFrame.next_sibling())
	{
		pugi::xml_node xmlJoints = xmlFrame.child("Skeleton").child("Joints");

		for (pugi::xml_node xmlJoint = xmlJoints.first_child(); xmlJoint; xmlJoint = xmlJoint.next_sibling())
		{
			float x = xmlJoint.attribute("x").as_float() * pos_scaler;
			float y = xmlJoint.attribute("y").as_float() * pos_scaler;
			float z = xmlJoint.attribute("z").as_float() * pos_scaler;

			FVector p = FVector(-x, z, -y) + pos_offset;

			if (FString() + xmlJoint.name() == "head")
			{
				Instantiate(BP_TestCube, transformFromVec(FVector(0, 0, 0), p, FVector(bp_scaler, bp_scaler, bp_scaler)));
			}
			else
			{
				Instantiate(BP_TestSphere, transformFromVec(FVector(0, 0, 0), p, FVector(bp_scaler, bp_scaler, bp_scaler)));
			}
		}
		break; // stop after one frame
	}

}
