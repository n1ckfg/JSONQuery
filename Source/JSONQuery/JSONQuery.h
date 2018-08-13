#pragma once

#include "ModuleManager.h"
//#include "Map.h"
#include "Engine/Engine.h"
#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"

DECLARE_LOG_CATEGORY_CLASS(JSONQueryLog, Log, All);

class FJSONQueryModule : public IModuleInterface
{

	public:
		virtual void StartupModule() override;
		virtual void ShutdownModule() override;

};