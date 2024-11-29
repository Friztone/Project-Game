#pragma once
#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include "Game.h"
#include "Setting.h"
#include "GameGUI.h"
#include "Destinite.h"

namespace Engine {
	class GameMain :public Engine::Game
	{
	public:
		GameMain(Setting* setting);
		~GameMain();
		virtual void Init();
		virtual void Update();
		virtual void Render();
	};
}

#endif