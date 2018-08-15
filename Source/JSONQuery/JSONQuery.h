#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

//#include "Map.h"
#include "Engine/Engine.h"
#include "Http.h"
#include "Json.h"

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