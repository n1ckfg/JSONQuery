// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class JSONQuery : ModuleRules
	{
        public JSONQuery(ReadOnlyTargetRules Target) : base(Target)
		{
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            //bEnforceIWYU = false;

            PublicIncludePaths.AddRange(
                new string[]
                {
                    "JSONQuery/Public"
                    // ... add public include paths required here ...
                }
            );



            PrivateIncludePaths.AddRange(
                new string[]
                {
                    "JSONQuery/Private"
                    // ... add other private include paths required here ...
                }
            );

            PublicDependencyModuleNames.AddRange(
                new string[] 
                {
                    "Core"
				    // ... add other public dependencies that you statically link with here ...
                }
            );

            PrivateDependencyModuleNames.AddRange(
				new string[] 
                {
					"CoreUObject",
					"Engine",
					"HTTP",
					"Json"
    				// ... add private dependencies that you statically link with here ...	
                }
            );
		}
	}
}