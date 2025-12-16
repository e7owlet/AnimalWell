// exiao from TongJi Universoty All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AnimalWellEditorTarget : TargetRules
{
	public AnimalWellEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange( new string[] { "AnimalWell" } );
	}
}
