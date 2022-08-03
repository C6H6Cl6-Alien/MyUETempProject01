// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TempProject01 : ModuleRules
{
	public TempProject01(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
