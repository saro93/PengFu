// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PenguinClub : ModuleRules
{
	public PenguinClub(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","UMG", "AIModule","GameplayTasks","PhysicsCore" });
	}
}
