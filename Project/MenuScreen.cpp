#include "MenuScreen.h"

Engine::MenuScreen::MenuScreen()
{
	text = NULL;
}

void Engine::MenuScreen::Init()
{
	Texture* mainMenuTexture = new Texture("mainmenu.png");
	mainMenuBg = (new Sprite(mainMenuTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);
	// Create a Texture
	Texture* texture = new Texture("buttons.png");
	Texture* logoTexture = new Texture("logo.png");
	logoText = (new Sprite(logoTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize(393, 95)->SetPosition((game->GetSettings()->screenWidth/2)- 196, (game->GetSettings()->screenHeight)-180);




	// Create Sprites
	Sprite* playSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)->SetNumYFrames(1)->AddAnimation("normal", 5, 5)->AddAnimation("hover", 3, 4)
		->AddAnimation("press", 3, 4)->SetAnimationDuration(400)->SetScale(0.5);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)->SetNumYFrames(1)->AddAnimation("normal", 2, 2)->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)->SetAnimationDuration(400)->SetScale(0.5);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->GetSettings()->screenWidth / 2) - (playSprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(playButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		250);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Add input mappings
	game->GetInputManager()->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);

}


void Engine::MenuScreen::Update()
{
	// Set background
	game->SetBackgroundColor(52, 155, 235);

	if (game->GetInputManager()->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("play" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("ingame");
		}
		else if ("exit" == b->GetButtonName()) {
			game->SetState(Engine::State::EXIT);
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::MenuScreen::Draw()
{
	mainMenuBg->Draw();
	logoText->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
}
