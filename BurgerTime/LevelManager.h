//
// Created by yasmi on 6/13/2026.
//

#ifndef MINIGIN_LEVELMANAGER_H
#define MINIGIN_LEVELMANAGER_H


#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

#pragma once
#include "Singleton.h"
#include <vector>
#include <string>

enum class GameMode { Single, Coop, VS };

class LevelManager : public dae::Singleton<LevelManager>
{
public:
    void Init(const std::vector<std::string>& levels);
    void NextLevel();
    void HighscoreLevel();
    void ResetGame(); // Called on Game Over or returning to Main Menu


    // --- State Getters ---
    int GetScore() const { return m_Score; }
    int GetLives() const { return m_Lives; }
    GameMode GetGameMode() const { return m_GameMode; }

    // --- State Setters ---
    void AddScore(int amount) { m_Score += amount; }
    void LoseLife() {
        --m_Lives;
    }

    void LoseSpray() {
        --m_Sprays;
    }

private:
    std::vector<std::string> m_LevelNames{};
    int m_CurrentIndex{ 0 };

    GameMode m_GameMode{ GameMode::Single };
    int m_Score{ 0 };
    int m_Lives{ 4 };
    int m_Sprays{5};
};

#endif //MINIGIN_LEVELMANAGER_H
