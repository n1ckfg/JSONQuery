#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"
#include "ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Http.h"
#include "Json.h"
#include "pugixml.hpp"

//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <exception>
//#include <cmath>

DECLARE_LOG_CATEGORY_CLASS(JSONQueryLog, Log, All);

class FJSONQueryModule : public IModuleInterface
{

	public:
		virtual void StartupModule() override;
		virtual void ShutdownModule() override;

};