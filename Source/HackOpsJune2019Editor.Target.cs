// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class HackOpsJune2019EditorTarget : TargetRules
{
	public HackOpsJune2019EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "HackOpsJune2019" } );
	}
}
