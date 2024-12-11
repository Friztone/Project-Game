#ifndef GAMEGUI_H
#define GAMEGUI_H

#include "Game.h"
#include "Setting.h"
#include "OnlyJumpScreen.h"
#include "MenuScreen.h"
#include "GameOverScreen.h"
#include "ScoreScreen.h"



namespace Engine {
	class GameGUI :public Engine::Game
	{
	public:
		GameGUI(Setting* setting);
		~GameGUI();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	};
}

#endif

