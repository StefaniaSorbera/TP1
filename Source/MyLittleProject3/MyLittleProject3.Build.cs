// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyLittleProject3 : ModuleRules
{
	public MyLittleProject3(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MyLittleProject3",
			"MyLittleProject3/Variant_Platforming",
			"MyLittleProject3/Variant_Platforming/Animation",
			"MyLittleProject3/Variant_Combat",
			"MyLittleProject3/Variant_Combat/AI",
			"MyLittleProject3/Variant_Combat/Animation",
			"MyLittleProject3/Variant_Combat/Gameplay",
			"MyLittleProject3/Variant_Combat/Interfaces",
			"MyLittleProject3/Variant_Combat/UI",
			"MyLittleProject3/Variant_SideScrolling",
			"MyLittleProject3/Variant_SideScrolling/AI",
			"MyLittleProject3/Variant_SideScrolling/Gameplay",
			"MyLittleProject3/Variant_SideScrolling/Interfaces",
			"MyLittleProject3/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
