#pragma once

namespace dae {

class Game {
public:
	Game();
	virtual ~Game();
	virtual void Initialize() = 0;
	//no render/update, inside initialize you should still add it to the scene, this will handle the draw for you.

	enum class GameMode {
		single,
		Coop,
		VS
	};

	GameMode currGameMode = GameMode::single;

};
}


//make other games inherite from game (abstract class)
// -> change the scene manager so you can 'set' the scenes
//amke sure to call intialize in the minigin!!
// -> maybe set function / pass in the constructor?
// engine should have ownership right....?
// -> look for a way to switch games out
// -> should call the new initializer then!
