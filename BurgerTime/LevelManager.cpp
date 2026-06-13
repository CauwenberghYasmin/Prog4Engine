//
// Created by yasmi on 6/13/2026.
//

#include "LevelManager.h"


#include "SceneManager.h"
#include "BurgerTime.h"

void LevelManager::Init(const std::vector<std::string>& levels)
{
    m_LevelNames = levels;
    m_CurrentIndex = 0;

}


void LevelManager::NextLevel() {
    m_CurrentIndex++;

    int index = m_CurrentIndex % m_LevelNames.size();

    // Switch the scene
    dae::SceneManager::GetInstance().SetScene(m_LevelNames[index]);
}

void LevelManager::HighscoreLevel() {
    dae::SceneManager::GetInstance().SetScene("HighScoreScene");
}

void LevelManager::ResetGame()
{
    m_CurrentIndex = 0;
    m_Lives = 4;
    m_Score = 0;
    m_Sprays = 5;
}