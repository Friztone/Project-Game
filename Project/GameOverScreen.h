#pragma once
#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "Screen.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include <vector>
#include "ScreenManager.h"

namespace Engine {
	class GameOverScreen :
		public Engine::Screen
	{
	public:
		GameOverScreen();
		void Init();
		void Update();
		void Draw();
		Sprite* gameOverBg = NULL;
		Sprite* gameOverText = NULL;
	private:
		vector<Button*> buttons;
		Text* text;
		int currentButtonIndex = 0;
	};
}

#endif