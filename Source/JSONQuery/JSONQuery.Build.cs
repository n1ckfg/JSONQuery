// Copyright 1998-2013 Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
	public class JSONQuery : ModuleRules
	{
        public JSONQuery(ReadOnlyTargetRules Target) : base(Target)
		{
			bEnforceIWYU = false;
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core", 
					"CoreUObject",
					"Engine",
					"HTTP",
					"Json"
                }
			);
		}
	}
}