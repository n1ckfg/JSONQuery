#include "JSONQuery.h"

#define LOCTEXT_NAMESPACE "JSONQueryModule"

void JSONQueryModule::StartupModule()
{
	// Startup LOG MSG
	UE_LOG(JSONQueryLog, Warning, TEXT("JSONQuery: Log Started"));
}

void JSONQueryModule::ShutdownModule()
{
	// Shutdown LOG MSG
	UE_LOG(JSONQueryLog, Warning, TEXT("JSONQuery: Log Ended"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(JSONQueryModule, JSONQuery);
