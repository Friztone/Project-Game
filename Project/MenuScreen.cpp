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
	Texture* texture = new Texture("button.png");
	Texture* logoTexture = new Texture("OnlyJump.png");
	logoText = (new Sprite(logoTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetPosition((game->GetSettings()->screenWidth / 2) - (logoTexture->GetWidth() / 2) * 0.8, (game->GetSettings()->screenHeight) / 1.3)-> SetScale(0.8);




	// Create Sprites
	Sprite* restartSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 3, 3)->AddAnimation("hover", 4, 5)
		->AddAnimation("press", 4, 5)->SetAnimationDuration(400)->SetScale(0.5);

	Sprite* scoreSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 12, 12)->AddAnimation("hover", 13, 14)
		->AddAnimation("press", 13, 14)->SetAnimationDuration(400)->SetScale(0.5);

	Sprite* menuSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(15)->SetNumYFrames(1)->AddAnimation("normal", 0, 0)->AddAnimation("hover", 1, 2)
		->AddAnimation("press", 1, 2)->SetAnimationDuration(400)->SetScale(0.5);

	//Create Buttons
	Button* restartButton = new Button(restartSprite, "restart");
	restartButton->SetPosition((game->GetSettings()->screenWidth / 2) - (restartSprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(restartButton);

	Button* scoreButton = new Button(scoreSprite, "score");
	scoreButton->SetPosition((game->GetSettings()->screenWidth / 2) - (scoreSprite->GetScaleWidth() / 2),
		275);
	buttons.push_back(scoreButton);

	Button* menuButton = new Button(menuSprite, "menu");
	menuButton->SetPosition((game->GetSettings()->screenWidth / 2) - (menuSprite->GetScaleWidth() / 2),
		150);
	buttons.push_back(menuButton);

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
		if ("restart" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("ingame");
		}
		else if ("score" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("score");
		}
		else if ("menu" == b->GetButtonName()) {
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
