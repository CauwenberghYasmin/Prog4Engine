#pragma once


class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};


class GameObject;
class GameActorCommand : public Command
{
	GameObject* m_actor; //make a GameActor class -> are gameobjects righttt
protected:
	GameObject* GetGameActor() const { return m_actor;}
public:
	//GameActorCommand(GameActor* actor);//constructor
	//virtual ~GameActorCommand();//don't delete -> does not own the pointer!

};


class SprayCommand : public GameActorCommand {
public:
	void Execute() override 
	{ 
		//GetGameActor()->Spray(); //put in cpp file so can include the h file
	} 
};

class MoveCommand : public GameActorCommand {
public:
	void Execute() override
	{
		//GetGameActor()->move();
	}
};


