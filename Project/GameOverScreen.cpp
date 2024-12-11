#include "GameOverScreen.h"

Engine::GameOverScreen::GameOverScreen()
{
	text = NULL;
}

void Engine::GameOverScreen::Init()
{
	Texture* mainMenuTexture = new Texture("mainmenu.png");
	gameOverBg = (new Sprite(mainMenuTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);
	// Create a Texture
	Texture* texture = new Texture("button.png");
	Texture* logoTexture = new Texture("GameOver.png");
	gameOverText = (new Sprite(logoTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetPosition((game->GetSettings()->screenWidth / 2) - (logoTexture->GetWidth()/2), (game->GetSettings()->screenHeight)/2);




	// Create Sprites
	Sprite* playSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 6, 6)->AddAnimation("hover", 7, 8)
		->AddAnimation("press", 7, 8)->SetAnimationDuration(400)->SetScale(0.4);

	Sprite* scoreSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 12, 12)->AddAnimation("hover", 13, 14)
		->AddAnimation("press", 13, 14)->SetAnimationDuration(400)->SetScale(0.4);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 9, 9)->AddAnimation("hover", 10, 11)
		->AddAnimation("press", 10, 11)->SetAnimationDuration(400)->SetScale(0.4);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->GetSettings()->screenWidth / 2) - (playSprite->GetScaleWidth() / 2) - 250,
		230);
	buttons.push_back(playButton);

	Button* scoreButton = new Button(scoreSprite, "score");
	scoreButton->SetPosition((game->GetSettings()->screenWidth / 2) - (scoreSprite->GetScaleWidth() / 2),
		230);
	buttons.push_back(scoreButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2) + 250,
		230);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Add input mappings
	game->GetInputManager()->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);

}


void Engine::GameOverScreen::Update()
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
		else if ("score" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("score");
		}
		else if ("exit" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::GameOverScreen::Draw()
{
	gameOverBg->Draw();
	gameOverText->Draw();

	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
}
