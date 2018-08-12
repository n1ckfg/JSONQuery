// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "JSONQuery.h"

//#include "Map.h"
#include "Engine/Engine.h"
#include "CoreMinimal.h"
#include "Http.h"
#include "Json.h"

#include "JSONFieldData.generated.h"

/**
* The possible status of a JSON POST/GET call.
*/
UENUM(BlueprintType, Category = "JSON")
enum class EJSONResult : uint8
{
	Success = 0,
	HttpFailed,
	JSONParsingFailed
};

// Generate a delegate for the OnGetResult event
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGetResult, const bool, bSuccess, class UJSONFieldData*, JSON, const EJSONResult, Status);

UCLASS(BlueprintType, Blueprintable, Category = "JSON")
class UJSONFieldData : public UObject
{
	GENERATED_BODY()

	public:
		UJSONFieldData();

		UObject* contextObject;

		TSharedPtr<FJsonObject> Data;

		UPROPERTY(BlueprintAssignable, Category = "JSON")
		FOnGetResult OnGetResult;

		UFUNCTION(BlueprintPure, meta = (DisplayName = "JSON To String", CompactNodeTitle = "->", Keywords = "cast text convert serialize"), Category = "JSON")
		FString ToString();

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Check Field Exists"), Category = "JSON")
		bool HasField(const FString& key);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Create JSON", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
		static UJSONFieldData* Create(UObject* WorldContextObject);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add String Field"), Category = "JSON")
		UJSONFieldData* SetString(const FString& key, const FString& value);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Boolean Field"), Category = "JSON")
		UJSONFieldData* SetBoolean(const FString& key, const bool value);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Float Field"), Category = "JSON")
		UJSONFieldData* SetFloat(const FString& key, const float value);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Integer Field"), Category = "JSON")
		UJSONFieldData* SetInt(const FString& key, const int32 value);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Null Field"), Category = "JSON")
		UJSONFieldData* SetNull(const FString& key);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add String Array Field"), Category = "JSON")
		UJSONFieldData* SetStringArray(const FString& key, const TArray<FString> data);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Boolean Array Field"), Category = "JSON")
		UJSONFieldData* SetBoolArray(const FString& key, const TArray<bool> data);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Float Array Field"), Category = "JSON")
		UJSONFieldData* SetFloatArray(const FString& key, const TArray<float> data);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Integer Array Field"), Category = "JSON")
		UJSONFieldData* SetIntArray(const FString& key, const TArray<int32> data);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Null Array Field"), Category = "JSON")
		UJSONFieldData* SetNullArray(const FString& key, const int32& length);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object Field"), Category = "JSON")
		UJSONFieldData* SetObject(const FString& key, const UJSONFieldData* objectData);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Add Object Array Field"), Category = "JSON")
		UJSONFieldData* SetObjectArray(const FString& key, const TArray<UJSONFieldData*> arrayData);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Field"), Category = "JSON")
		FString GetString(const FString& key, bool& success) const;

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Boolean Field"), Category = "JSON")
		bool GetBool(const FString& key, bool& success) const;

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Integer Field"), Category = "JSON")
		int32 GetInt(const FString& key, bool& success) const;

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Float Field"), Category = "JSON")
		float GetFloat(const FString& key, bool& success) const;

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Field Is Null"), Category = "JSON")
		bool GetIsNull(const FString& key, bool& fieldExists) const;

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get String Array Field"), Category = "JSON")
		TArray<FString> GetStringArray(const FString& key, bool& success);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Boolean Array Field"), Category = "JSON")
		TArray<bool> GetBoolArray(const FString& key, bool& success);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Integer Array Field"), Category = "JSON")
		TArray<int32> GetIntArray(const FString& key, bool& success);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Float Array Field"), Category = "JSON")
		TArray<float> GetFloatArray(const FString& key, bool& success);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Field", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
		UJSONFieldData* GetObject(const FString& key, bool& success);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Array Field", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
		TArray<UJSONFieldData*> GetObjectArray(UObject* WorldContextObject, const FString& key, bool& success);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Object Keys", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
		TArray<FString> GetObjectKeys(UObject* WorldContextObject);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "From String"), Category = "JSON")
		bool FromString(const FString& dataString);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "From File"), Category = "JSON")
		bool FromFile(const FString& FilePath);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Post JSON Request", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
		void PostRequest(UObject* WorldContextObject, const FString& url);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Post JSON Request and File"), Category = "JSON")
		void PostRequestWithFile(FString FilePath, const FString& Url);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get JSON Request", HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"), Category = "JSON")
		static UJSONFieldData* GetRequest(UObject* WorldContextObject, const FString& url);

		// Saves text input to a file.
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Save String to File"), Category = "JSON")
		static bool SaveStringTextToFile(FString SaveDirectory, FString FileName, FString SaveText, bool AllowOverWriting = false);

	private:
		void OnReady(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
		
		void Reset();
		
		static FString CreateURL(FString inputURL);
		
		void WriteObject(TSharedRef<TJsonWriter<TCHAR>> writer, FString key, FJsonValue* value);

};