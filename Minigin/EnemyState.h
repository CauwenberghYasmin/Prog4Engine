
//NO STATIC STATES SINCE THERE ARE MULTIPLE INSTANCES OF THIS IN THE GAME!
#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include <memory>
#include "GameObject.h"


class EnemyState //is interface. (look how to connect everything (component? need to call update in actual update too!))
{
public:
	virtual ~EnemyState() = default;


	//for switching states (mostly stun one)
	virtual void OnEnter(dae::GameObject* pOwner, const std::vector<dae::GameObject*>& players) =0;
	virtual void OnExit(dae::GameObject* pOwner)=0;

	virtual std::unique_ptr<EnemyState> Update(dae::GameObject* pOwner) = 0; //return new state pointer
};
#endif // ENEMYSTATE_H
