// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectInn : ModuleRules
{
	public ProjectInn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "ProjectInn" });
        PrivateIncludePaths.AddRange(new string[] { "ProjectInn" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" ,"StateMachineModule" });

        PrivateDependencyModuleNames.AddRange(new string[] { "StateMachineModule" });
    }
}
