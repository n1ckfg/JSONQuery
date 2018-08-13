#include "JSONQuery.h"

#define LOCTEXT_NAMESPACE "FJSONQueryModule"

void FJSONQueryModule::StartupModule()
{
	// Startup LOG MSG
	UE_LOG(JSONQueryLog, Warning, TEXT("JSONQuery: Log Started"));
}

void FJSONQueryModule::ShutdownModule()
{
	// Shutdown LOG MSG
	UE_LOG(JSONQueryLog, Warning, TEXT("JSONQuery: Log Ended"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FJSONQueryModule, JSONQuery);
