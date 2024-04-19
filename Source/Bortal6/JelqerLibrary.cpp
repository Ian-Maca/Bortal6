// Fill out your copyright notice in the Description page of Project Settings.


#include "JelqerLibrary.h"

#include "GameFramework/GameUserSettings.h"

bool _toggler = true;


void UJelqerLibrary::SettingsChanger()
{

	if (!GEngine) { return; }
	
	UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();

	const EWindowMode::Type CurrentMode = UserSettings->GetFullscreenMode();
	
	if (CurrentMode == EWindowMode::WindowedFullscreen)
	{
		UserSettings->SetFullscreenMode(EWindowMode::Windowed);
		UserSettings->SetScreenResolution(FIntPoint(1024, 680));
		UE_LOG(LogTemp, Warning, TEXT("Toggling fullscreen to windowed"))
	}
	else if (CurrentMode == EWindowMode::Windowed)
	{
		UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);
		UserSettings->SetScreenResolution(FIntPoint(1920, 1080));
		UE_LOG(LogTemp, Warning, TEXT("Toggling fullscreen to fullscreen"))
	}
	
	UserSettings->ApplySettings(false);
}
