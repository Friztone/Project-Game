#include "ScoreScreen.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

Engine::ScoreScreen::ScoreScreen()
{
}

void Engine::ScoreScreen::Init()
{

    Texture* bgTexture = new Texture("lavaScore.png");
    backgroundSprite = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
        ->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);

    // Add input mappings
    game->GetInputManager()->AddInputMapping("mainmenu", SDLK_ESCAPE);

    // Initialize text objects
    float gap = 50.0f; // Gap between each score line

    for (int i = 0; i < 5; ++i) {
        Text* scoreText = new Text("Gunplay-Regular 400.ttf", 48, game->GetDefaultTextShader());
        scoreText->SetScale(1.0f)->SetColor(255, 255, 255)->SetPosition((game->GetSettings()->screenWidth / 2) / 1.3, (game->GetSettings()->screenHeight / 2) * 1.2 - (i * gap));
        scoreTexts.push_back(scoreText);
    }

    title = new Text("Gunplay-Regular 400.ttf", 64, game->GetDefaultTextShader());
    title->SetScale(1.0f)->SetColor(255, 255, 255)->SetPosition(((game->GetSettings()->screenWidth) / 2) / 1.5, game->GetSettings()->screenHeight - (title->GetFontSize() * title->GetScale()) * 2);

    guide = new Text("Gunplay-Regular 400.ttf", 32, game->GetDefaultTextShader());
    guide->SetScale(1.0f)->SetColor(255, 255, 255)->SetPosition(((game->GetSettings()->screenWidth) / 2) / 1.5, 0 + (guide->GetFontSize() * guide->GetScale()) * 1.5);



}

void Engine::ScoreScreen::Update()
{
    // Load scores from file
    LoadScores();

    if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
        ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
    }

    // Update score texts
    for (size_t i = 0; i < scores.size() && i < scoreTexts.size(); ++i) {
        scoreTexts[i]->SetText(std::to_string(i+1) + ".  " + std::to_string(scores[i]));
    }

    title->SetText("HIGH SCORES");
    guide->SetText("Press Esc to Main Menu");
}

void Engine::ScoreScreen::Draw()
{
    backgroundSprite->Draw();

    for (auto& text : scoreTexts) {
        text->Draw();
    }

    title->Draw();
    guide->Draw();
}

void Engine::ScoreScreen::LoadScores()
{
    std::ifstream scoresFile("scores.txt");
    if (!scoresFile.is_open()) {
        // If the file doesn't exist
        std::ofstream outFile("scores.txt");
        for (int i = 0; i < 5; ++i) {
            outFile << "0\n";
            scores.push_back(0);
        }
        outFile.close();
    }
    else {
        scores.clear();
        int score;
        while (scoresFile >> score) {
            scores.push_back(score);
        }
        scoresFile.close();
    }

    // Ensure scores list has exactly 5 entries
    while (scores.size() < 5) {
        scores.push_back(0);
    }
    scores.resize(5);
}

void Engine::ScoreScreen::SaveScore()
{
    // Add the new score to the list and sort
    scores.push_back(score);
    std::sort(scores.rbegin(), scores.rend()); // Sorting

    // Ensure only top 5 scores are kept
    if (scores.size() > 5) {
        scores.resize(5);
    }

    // Write the scores back to the file
    std::ofstream scoresFile("scores.txt");
    if (scoresFile.is_open()) {
        for (int s : scores) {
            scoresFile << s << "\n";
        }
        scoresFile.close();
    }
}
