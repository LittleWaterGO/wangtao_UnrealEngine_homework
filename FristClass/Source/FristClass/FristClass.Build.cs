// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FristClass : ModuleRules
{
	public FristClass(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
