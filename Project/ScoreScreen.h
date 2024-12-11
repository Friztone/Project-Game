#pragma once
#pragma once
#ifndef SCORESCREEN_H
#define SCORESCREEN_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Screen.h"
#include "Turtle.h"
#include "Music.h"
#include "Sound.h"
#include "ScreenManager.h"
#include "Text.h"
#include <vector>



namespace Engine {
	class ScoreScreen :
		public Engine::Screen
	{
	public:
		ScoreScreen();
		void Init();
		void Update();
		void Draw();
		void LoadScores();
		void SaveScore();		
	private:
		Engine::Sprite* CreateSprite(Texture* texture);
		Texture* dotTexture = NULL;
		vector<Sprite*> platforms;
		vector<Sprite*> lavaSprites;
		Sprite* backgroundSprite = NULL;
		Sprite* characterSprite = NULL;
		Sprite* lavaSprite = NULL;
		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;
		Music* music = NULL;;
		Sound* sound = NULL;
		Sound* soundGameOver = NULL;
		Text* title = NULL;
		Text* guide = NULL;
		Text* highScoreText = NULL;
		std::vector<Text*> scoreTexts;
		std::vector<int> scores;

		int score = 0;
		int highScore = 0;
	};
}

#endif