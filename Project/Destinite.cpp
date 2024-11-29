#include "Destinite.h"

Engine::Destinite::Destinite(Setting* setting) : Engine::Game(setting)
{
    setting->windowTitle = "Destinite";
}

Engine::Destinite::~Destinite()
{
    delete texture;
    delete sprite;
    delete npcTexture;
    delete npcSprite;
}

void Engine::Destinite::Init()
{
    texture = new Texture("Knight.png");
    sprite = new Sprite(texture, defaultSpriteShader, defaultQuad);
    sprite->SetNumXFrames(10)->SetNumYFrames(3)->AddAnimation("idle", 0, 9)
        ->AddAnimation("walk", 10, 19)->AddAnimation("attack", 20, 25)
        ->SetScale(1.5)->SetAnimationDuration(200)->SetPosition(300, 0);

    npcTexture = new Texture("NPC.png");
    npcSprite = new Sprite(npcTexture, defaultSpriteShader, defaultQuad);
    npcSprite->SetNumXFrames(22)->SetNumYFrames(5)->AddAnimation("npc_walk", 22, 33)->AddAnimation("npc_attack", 44, 58)
        ->SetScale(0.7)->SetAnimationDuration(100)->SetPosition(100, 0);

    // Input mappings
    inputManager->AddInputMapping("walk-left", SDLK_LEFT)
        ->AddInputMapping("walk-right", SDLK_RIGHT)
        ->AddInputMapping("jump", SDLK_UP)
        ->AddInputMapping("Attack", SDLK_x);

    SetBackgroundColor(65, 180, 242);
}

void Engine::Destinite::Update()
{
    sprite->Update(GetGameTime());

    float x = sprite->GetPosition().x;
    float y = sprite->GetPosition().y;
    float velocity = 0.1f;
    bool isAttacking = false;

    sprite->PlayAnim("idle");

    if (inputManager->IsKeyPressed("walk-right")) {
        x += velocity * GetGameTime();
        sprite->SetFlipHorizontal(false)->PlayAnim("walk");
    }

    if (inputManager->IsKeyPressed("walk-left")) {
        x -= velocity * GetGameTime();
        sprite->SetFlipHorizontal(true)->PlayAnim("walk");
    }

    // Jump logic
    if (inputManager->IsKeyPressed("jump") && !jump)
    {
        float ratio = (GetGameTime() / 55.7f);
        gravity = 0.14f * ratio;
        yVelocity = 0.8f;
        jump = true;
        sprite->PlayAnim("jump");
    }

    if (y > 0) {
        yVelocity -= gravity;
    }
    else if (y < 0) {
        jump = false;
        yVelocity = 0;
        y = 0;
        sprite->PlayAnim("walk");
    }

    y += yVelocity * GetGameTime();
    sprite->SetPosition(x, y);

    if (inputManager->IsKeyPressed("Attack") && !isAttacking) {
        sprite->PlayAnim("attack");
        isAttacking = true;
    }


    ControlNPC();

    sprite->SetPosition(x, y)->Update(GetGameTime());
}

void Engine::Destinite::ControlNPC()
{
    vec2 npcPosition = npcSprite->GetPosition();
    vec2 playerPosition = sprite->GetPosition();

    float npcSpeed = 0.05f;
    float attackDistance = 50.0f;

    float distance = length(npcPosition - playerPosition);



    if (distance > attackDistance) {
        if (npcPosition.x < playerPosition.x) {
            npcPosition.x += npcSpeed * GetGameTime();
            npcSprite->SetFlipHorizontal(true);
            npcSprite->PlayAnim("npc_walk");
        }
        else if (npcPosition.x > playerPosition.x) {
            npcPosition.x -= npcSpeed * GetGameTime();
            npcSprite->SetFlipHorizontal(false);
            npcSprite->PlayAnim("npc_walk");
        }
        npcSprite->SetPosition(npcPosition.x, npcPosition.y)->Update(GetGameTime());

    }
    else {
        npcSprite->PlayAnim("npc_attack");
        npcSprite->SetPosition(npcPosition.x, npcPosition.y)->Update(GetGameTime());

    }
}

void Engine::Destinite::Render()
{
    npcSprite->Draw();
    sprite->Draw();
}