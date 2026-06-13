#pragma once
#include "Game.h"
#include "GameObject.h"

namespace dae {

	class Scene;
class BurgerTime final : public Game
{
public:
	BurgerTime();
	virtual ~BurgerTime() override;

	virtual void Initialize() override; //make all scenes + set startscreen
	//make functions to create other scenes (objects)

	//setScenes done in observer if conditions are met!
	//to unload scene, just clear the object vector :>


	//See how long it takes for each scene to load/unload -> otherwise make a loading scene :> (set image -> do loading/unloading (would freeze) and once done continue) Or maybe on a seperate thread??

	void LoadStartScreen(Scene* scene); //exam question: why made this function static -> BE ABLE TO ANSWER!
	void LoadLevel01(Scene* scene); //exam question: why made this function static -> BE ABLE TO ANSWER!
	 void LoadLevel02(Scene* scene);
	 void LoadLevel03(Scene* scene);
	 void LoadHighScore(Scene* scene);
	//void LoadStartScreen(Scene* scene);
	//void LoadEndScreen(Scene* scene); //highscore!

	bool m_GameStarted{false};

	BurgerTime(const BurgerTime& other) = delete;
	BurgerTime& operator=(const BurgerTime& other) = delete;
	BurgerTime(BurgerTime&& other) = delete;
	BurgerTime& operator=(BurgerTime&& other) = delete;

private:
	void SetupPlayersAndUI(dae::Scene* scene, std::vector<GameObject*>& players, glm::vec2& positionPlayer01, glm::vec2& positionPlayer02);
}; //cpp file should have to load funciton from main
}
