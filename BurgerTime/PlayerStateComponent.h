//
// Created by yasmi on 6/12/2026.
//

#ifndef MINIGIN_PLAYERSTATECOMPONENT_H
#define MINIGIN_PLAYERSTATECOMPONENT_H

#include "Component.h"
#include "GameObject.h"

class PlayerStateComponent final: public dae::Component //THIS IS NOT THE STATE WE'VE SEEN IN CLASS
{   //THIS IS MORE OF AN STATIC RESOURCES FILE FOR THE PLAYERS!!!!
public:
    PlayerStateComponent(dae::GameObject* owner, int id =0);

    void Update() override;
    void Render() override;

    //facing direction
    enum Direction {Up, Down, Left, Right};
    void SetDirection(int direction) {
        m_CurrDirection = static_cast<Direction>(direction);
    }


    static int m_ScoreAmount;
    // lives can be static in healthComp, goes over files + shared in multiplayer! (reset when looping)

    //SET IN DIFF OBJECTS, BUT KEPT HERE TO SURVIVE OVER THE SCENELEVELS

    Direction m_CurrDirection = Direction::Right; //not static, each own version
private:

};


#endif //MINIGIN_PLAYERSTATECOMPONENT_H
