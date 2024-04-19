// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Bortal6 : ModuleRules
{
	public Bortal6(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "CableComponent"});
	}
}
