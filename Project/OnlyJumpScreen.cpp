#include "OnlyJumpScreen.h"

Engine::OnlyJumpScreen::OnlyJumpScreen()
{
}

void Engine::OnlyJumpScreen::Init()
{
	// Spawn setting
	maxSpawnTime = 1000;
	numObjectPerSpawn = 1;
	numObjectsInPool = 100;

	Texture* bgTexture = new Texture("background.png");
	backgroundSprite = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);

	// Load lava texture and create ground sprite
	Texture* lavaTexture = new Texture("lava.png");
	lavaSprite = new Sprite(lavaTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	lavaSprite->SetSize(137, 50);
	lavaSprite->SetPosition(0, 0);

	float screenWidth = game->GetSettings()->screenWidth;
	float lavaWidth = 137;
	float lavaHeight = 50;
	int numLavaSprites = (int)ceil(screenWidth / lavaWidth) + 1;

	for (int i = 0; i < numLavaSprites; i++) {
		Sprite* lava = new Sprite(lavaTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		lava->SetSize(lavaWidth, lavaHeight);
		lava->SetPosition(i * lavaWidth, 0);
		lavaSprites.push_back(lava);
	}

	// Generate Platforms
	Texture* platformTexture = new Texture("Platforms.png");
	vec2 start = vec2(200, 90);
	for (int i = 0; i < 4; i++) {
		Sprite* platformSprite = new Sprite(platformTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		platformSprite->SetSize(150, 32)->SetPosition(start.x + i * 210, start.y + i * (game->GetSettings()->screenHeight)/4);
		platformSprite->SetBoundingBoxSize(platformSprite->GetScaleWidth() - (16 * platformSprite->GetScale()), platformSprite->GetScaleHeight());
		platforms.push_back(platformSprite);
	}

	// Load a texture
	Texture* texture = new Texture("Meteors.png");
	for (int i = 0; i < numObjectsInPool; i++) {
		Turtle* o = new Turtle(CreateSprite(texture));
		objects.push_back(o);
	}

	Texture* characterTexture = new Texture("Knight.png");
	characterSprite = new Sprite(characterTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	characterSprite->SetPosition(420, 35)->SetNumXFrames(10)->SetNumYFrames(3)->SetAnimationDuration(30)->SetScale(1.5f)->AddAnimation("idle", 0, 9)->AddAnimation("walk", 10, 19);
	characterSprite->SetBoundingBoxSize(characterSprite->GetScaleWidth() - (90 * characterSprite->GetScale()),
	characterSprite->GetScaleHeight() - (45 * characterSprite->GetScale()));

	// Add input mappings
	game->GetInputManager()->AddInputMapping("mainmenu", SDLK_ESCAPE);
	game->GetInputManager()->AddInputMapping("right", SDLK_RIGHT);
	game->GetInputManager()->AddInputMapping("left", SDLK_LEFT);
	game->GetInputManager()->AddInputMapping("jump", SDLK_SPACE);

	text = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	text->SetScale(1.0f)->SetColor(255, 255, 255)->SetPosition(0, game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()));
	highScoreText = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	highScoreText->SetScale(1.0f)->SetColor(255, 255, 255)->SetPosition(0, game->GetSettings()->screenHeight - (highScoreText->GetFontSize() * 2 * highScoreText->GetScale()));



	// This dot sprite is for visual debugging (to see the actual bounding box) 
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite2 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite3 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite4 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());

	music = (new Music("backsound.ogg"))->SetVolume(40)->Play(true);

	sound = (new Sound("jumpSound.wav"))->SetVolume(100);
	soundGameOver = (new Sound("gameOver.wav"))->SetVolume(100);

}

void Engine::OnlyJumpScreen::Update()
{
	// Back to main menu
	if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
		Reset();
	}

	characterSprite->PlayAnim("idle");

	// Move lava sprites to the left
	float lavaSpeed = 0.03f; // Adjust speed as needed
	for (Sprite* lava : lavaSprites) {
		vec2 lavaPos = lava->GetPosition();
		lavaPos.x -= lavaSpeed * game->GetGameTime(); // Move to the left
		lava->SetPosition(lavaPos.x, lavaPos.y);

		// Check if the lava sprite is off-screen to the left
		if (lavaPos.x + lava->GetScaleWidth() < 0) {
			// Move it to the right end of the screen
			float maxRight = game->GetSettings()->screenWidth;
			lava->SetPosition(maxRight, lavaPos.y);
		}
	}


	// Move character sprite using keyboard
	vec2 oldCharPos = characterSprite->GetPosition();
	float x = oldCharPos.x, y = oldCharPos.y;
	if (game->GetInputManager()->IsKeyPressed("right")) {
		x += 0.6f * game->GetGameTime();
		characterSprite->PlayAnim("walk")->SetFlipHorizontal(false);
	}

	if (game->GetInputManager()->IsKeyPressed("left")) {
		x -= 0.6f * game->GetGameTime();
		characterSprite->PlayAnim("walk")->SetFlipHorizontal(true);
	}

	characterSprite->SetPosition(x, y);

	if (y < 0) { // Check if character's Y position is below the screen
		ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
		Reset();
		soundGameOver->Play(false);
		return;
	}

	// Portal screen wrapping: jika karakter keluar dari layar, pindahkan ke sisi sebaliknya
	float screenWidth = game->GetSettings()->screenWidth;
	float characterWidth = characterSprite->GetScaleWidth();

	if (x > screenWidth) {
		x = -characterWidth;
	}
	else if (x < -characterWidth) {
		x = screenWidth;
	}

	characterSprite->SetPosition(x, y);


	float platformFallSpeed = 0.1f + (score / 10000.0f);
	for (Sprite* s : platforms) {
		

		vec2 platformPos = s->GetPosition();
		platformPos.y -= platformFallSpeed * game->GetGameTime(); // Move down
		s->SetPosition(platformPos.x, platformPos.y);

		// Reset platform position if it goes off-screen
		if (platformPos.y + s->GetScaleHeight() < 0) {
			platformPos.y = game->GetSettings()->screenHeight; // Reset to top

			// Randomize x position within screen bounds
			float randomX = (float)(rand() % (int)(game->GetSettings()->screenWidth - s->GetScaleWidth()));
			platformPos.x = randomX;

			s->SetPosition(platformPos.x, platformPos.y);
			score+=50;
		}

		// Check collision with character
		if (s->GetBoundingBox()->CollideWith(characterSprite->GetBoundingBox())) {
			// Revert x position if collided
			x = oldCharPos.x;
			characterSprite->SetPosition(x, y);
			break;
		}
	}

	if (score > highScore) {
		highScore = score;  // Update high score
	}

	if (game->GetInputManager()->IsKeyPressed("jump") && !jump) {
		//Set gravity and yVelocity
		float ratio = (game->GetGameTime() / 16.7f);
		gravity = 0.06f * ratio;
		yVelocity = 1.8f;
		jump = true;
		sound->Play(false);
	}

	if (y > 0) {
		yVelocity -= gravity;
	}
	else if (y < 0) {
		jump = false;
		yVelocity = 0;
		y = 0;
	}


	y += yVelocity * game->GetGameTime();
	characterSprite->SetPosition(x, y);

	for (Sprite* s : platforms) {
		if (s->GetBoundingBox()->CollideWith(characterSprite->GetBoundingBox())) {
			//revert y position if collided
			y = oldCharPos.y;
			characterSprite->SetPosition(x, y);

			//and set jump to false and yVelovity to 0
			yVelocity = 0;
			jump = false;
			break;
		}
	}

	// Set background
	game->SetBackgroundColor(255, 255, 255);

	// Time to spawn objects
	if (spawnDuration >= maxSpawnTime) {
		SpawnObjects();
		spawnDuration = 0;
	}
	// Update all objects
	for (Turtle* o : objects) {
		o->Update((game->GetGameTime()));
	}
	// Count spawn duration
	spawnDuration += (game->GetGameTime());

	text->SetText(("Score = " + to_string(score)));
	highScoreText->SetText(("High Score = " + to_string(highScore)));


	characterSprite->Update(game->GetGameTime());

	BoundingBox* bb = characterSprite->GetBoundingBox();
	dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
		bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
	dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
		bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
	dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
		bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
	dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
		bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));

}

void Engine::OnlyJumpScreen::Draw()
{
	backgroundSprite->Draw();
	// Render all objects
	for (Turtle* o : objects) {
		o->Draw();
	}
	characterSprite->Draw();

	for (Sprite* s : platforms) {
		s->Draw();
	}

	//dotSprite1->Draw();
	//dotSprite2->Draw();
	//dotSprite3->Draw();
	//dotSprite4->Draw();

	for (Sprite* lava : lavaSprites) {
		lava->Draw();
	}

	text->Draw();
	highScoreText->Draw();



}

Engine::Sprite* Engine::OnlyJumpScreen::CreateSprite(Texture* texture)
{
	return (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(3)->SetNumYFrames(1)
		->AddAnimation("idle", 0, 3)->PlayAnim("idle")->SetScale(1.5)->SetAnimationDuration(100);
}

void Engine::OnlyJumpScreen::SpawnObjects()
{
	//Find Die object to reuse for spawning
	int spawnCount = 0;
	for (Turtle* o : objects) {
		if (spawnCount == numObjectPerSpawn) {
			break;
		}
		if (o->IsDie()) {
			// Set state to spawn

			// Random spawn position
			int min = 0;
			int max = (int)(game->GetSettings()->screenWidth - o->GetWidth());
			float x = (float)(rand() % (max - min + 1) + min);
			float y = game->GetSettings()->screenHeight + o->GetHeight();
			o->SetSpawn()->SetPosition(x, y);
			spawnCount++;
		}
	}
}

void Engine::OnlyJumpScreen::Reset() {
	// Reset karakter ke posisi awal
	characterSprite->SetPosition(420, 300);
	characterSprite->SetScale(1.5f);
	characterSprite->PlayAnim("idle");
	characterSprite->SetBoundingBoxSize(characterSprite->GetScaleWidth() - (90 * characterSprite->GetScale()),
		characterSprite->GetScaleHeight() - (45 * characterSprite->GetScale()));
	jump = false;
	yVelocity = 0;

	// Reset semua platform ke posisi awal
	for (int i = 0; i < 4; i++) {
		platforms[i]->SetPosition(200 + i * 210, 90 + i * (game->GetSettings()->screenHeight)/4); // Posisi platform kembali ke posisi semula
	}

	// Reset lava sprites
	for (int i = 0; i < lavaSprites.size(); i++) {
		lavaSprites[i]->SetPosition(i * 137, 0); // Posisi lava kembali ke posisi semula
	}

	// Reset waktu spawn
	spawnDuration = 0;
	maxSpawnTime = 1000;
	score = 0;
}


