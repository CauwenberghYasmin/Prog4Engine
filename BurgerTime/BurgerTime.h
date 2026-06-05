#pragma once
#include "Game.h"

namespace dae {

	class Scene;
class BurgerTime final : public Game
{
public:
	BurgerTime();
	virtual ~BurgerTime() override;

	virtual void Initialize() override; //make all scenes + set startscreen
	//make functions to create other scenes (objects)

	//setScenes done in observer if conditions are met! ->will need to have to loadscene function (set that one in the initialize! soa acces!)
	//to unload scene, just clear the object vector :>

	void LoadLevel01(Scene* scene);
private:

}; //cpp file should have to load funciton from main 
}