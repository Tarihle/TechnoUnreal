// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MegatronEnemies : ModuleRules
{
	public MegatronEnemies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "SkeletalMerging", "GameplayTags", "UMG" });

        //PublicIncludePaths.AddRange(new string[] { "SkeletalMergingLibrary/Public/SkeletalMergingLibrary.h" });
    }
}
