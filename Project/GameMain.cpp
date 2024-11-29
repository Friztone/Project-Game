//#include "GameMain.h"
//
//
//Engine::GameMain::GameMain(Setting* setting) :Engine::Game(setting)
//{
//	setting->windowTitle = "Destinite";
//}
//
//Engine::GameMain::~GameMain()
//{
//}
//
//void Engine::GameMain::Init()
//{
//	Setting* setting = new Setting();
//	Engine::ScreenManager::GetInstance(this)->AddScreen("Destinite", new GameGUI())
//		->AddScreen("mainmenu", new GameGUI())->SetCurrentScreen("mainmenu");
//}
//
//void Engine::GameMain::Update()
//{
//	Engine::ScreenManager::GetInstance(this)->Update();
//}
//
//void Engine::GameMain::Render()
//{
//	Engine::ScreenManager::GetInstance(this)->Draw();
//}