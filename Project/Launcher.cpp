#include "Setting.h"
#include "Game.h"

#include "GameGUI.h"
#include "OnlyJumpScreen.h"



int main(int argc, char** argv) {
	Engine::Setting* setting = new Engine::Setting();
	setting->screenWidth = 1280;
	setting->screenHeight = 720;
	setting->windowFlag = Engine::WindowFlag::WINDOWED;
	setting->vsync = false;
	setting->targetFrameRate = 60;
	setting->timeScale = 1;
	Engine::Game* game = new Engine::GameGUI(setting);
	game->Run();
	delete setting;
	delete game;

	return 0;
}
