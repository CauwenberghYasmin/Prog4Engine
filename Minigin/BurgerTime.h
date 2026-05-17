#pragma once
#include "Game.h"

namespace dae {

class BurgerTime final : public Game
{
public:
	BurgerTime();
	virtual ~BurgerTime() override;

	virtual void Initialize() override; //put everything from main in here!

private:

}; //cpp file should have to load funciton from main 
}