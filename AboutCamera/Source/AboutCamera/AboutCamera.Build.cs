// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AboutCamera : ModuleRules
{
	public AboutCamera(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
