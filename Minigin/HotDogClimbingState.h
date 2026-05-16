#pragma once
#include "HotDogState.h"


//LADDER
class HotDogClimbingState final: public HotDogState
{
public:
	
	//in update:
	// if reaches end ladder
	// go back to walking state!
	//if touches spray cloud -> go to stun state!
	//if touched by falling bun && bun.attack == true
	// go to crushed state!

private:


};