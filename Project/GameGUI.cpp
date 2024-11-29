#include "GameGUI.h"

Engine::GameGUI::GameGUI(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "Only Jump";
}

Engine::GameGUI::~GameGUI()
{
}

void Engine::GameGUI::Init()
{
	Engine::ScreenManager::GetInstance(this)->AddScreen("ingame", new OnlyJumpScreen())
		->AddScreen("mainmenu", new MenuScreen())->SetCurrentScreen("mainmenu");

}

void Engine::GameGUI::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();
}

void Engine::GameGUI::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();
}





