// exiao from TongJi Universoty All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class AnimalWellTarget : TargetRules
{
	public AnimalWellTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange( new string[] { "AnimalWell" } );
	}
}
