#pragma once
#ifndef DESTINITE_H
#define DESTINITE_H

#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"

namespace Engine {
	class Destinite :public Engine::Game
	{
	public:
		Destinite(Setting* setting);
		~Destinite();
		virtual void Init();
		virtual void Update();
		virtual void Render();
		virtual void ControlNPC();

	private:
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
		Engine::Texture* npcTexture = NULL;
		Engine::Sprite* npcSprite = NULL;

		vector<Sprite*> platforms;

		float yVelocity = 0, gravity = 0;
		bool jump = false, debug = false;
	};
}


#endif

