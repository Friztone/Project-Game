#pragma once
#ifndef ONLUJUMPSCSREEN_H
#define ONLUJUMPSCSREEN_H

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
	class OnlyJumpScreen :
		public Engine::Screen
	{
	public:
		OnlyJumpScreen();
		void Init();
		void Update();
		void Draw();
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
		Text* text = NULL;
		Text* highScoreText = NULL;

		void SpawnObjects();
		void Reset();
		int score = 0;
		int highScore = 0;
		vector<Turtle*> objects;
		float spawnDuration = 0, maxSpawnTime = 0, numObjectsInPool = 0, numObjectPerSpawn = 0;
		float yVelocity = 0, gravity = 0;
		bool jump = false, debug = false;
	};
}

#endif