// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class StateMachineModule: ModuleRules
{
    public StateMachineModule(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "AIModule"});

        PublicIncludePaths.AddRange(new string[] { "StateMachine" });

        PrivateIncludePaths.AddRange(new string[] { "StateMachine"});
    }
}
