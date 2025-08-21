// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GasFinally : ModuleRules
{
	public GasFinally(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
            "GameplayAbilities", 
			"GameplayTags", 
			"GameplayTasks"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"GasFinally",
			"GasFinally/Variant_Platforming",
			"GasFinally/Variant_Combat",
			"GasFinally/Variant_Combat/AI",
			"GasFinally/Variant_SideScrolling",
			"GasFinally/Variant_SideScrolling/Gameplay",
			"GasFinally/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
