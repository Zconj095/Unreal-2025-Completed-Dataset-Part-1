// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PEKBGGAP : ModuleRules
{
	public PEKBGGAP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "AssetRegistry", "XmlParser", "Sockets", "Networking", "RenderCore", "RHI" });

        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "Json", "JsonUtilities", "ImageWrapper", "Renderer", "Niagara" });

        PrivateIncludePaths.Add("PEKBGGAP/Private");

        // Note: Shader directory is registered at runtime in PEKBGGAP.cpp via
        // AddShaderSourceDirectoryMapping("/PEKBGGAP", <Module>/Private/Shaders).
        // The older UBT property PublicAdditionalShaderDirectories is not used in UE 5.6.

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "LevelEditor", "ToolMenus", "UnrealEd" });
        }

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
