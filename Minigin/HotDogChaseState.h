#pragma once
#include "HotDogState.h"


class HotDogChaseState final : public HotDogState
{
public:
	//virtual ~HotDogChaseState() override;
	//virtual void Update(HotDogState& hotdog) override;

	//start chase: see what direction to walk to:
	//if touches ladder: will go up->climb
	//if touches spray :go to stun state
	//if touches falling bun -> go to crush state!

private:
	//save target (determines which direction the hotdog should walk towards)
	//THEY DONT GO BACKWARDS, SO ONLY RECALC AFTER LADDER

};