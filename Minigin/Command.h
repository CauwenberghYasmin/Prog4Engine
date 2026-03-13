#pragma once

//go  over inheritance notes again to make sure!! (virtual, etc...)

class Command
{
public:
	virtual ~Command() = default;
	virtual void Execute() = 0;
};


class GameObject;
class GameObjectCommand : public Command
{
	GameObject* m_GameObject; //cache object that calls it!
protected:
	GameObject* GetGameObject() const { return m_GameObject;}
public:
	explicit GameObjectCommand(GameObject* pGameObject);
	virtual ~GameObjectCommand() = default;//don't delete -> does not own the pointer!
};



class MoveCommand : public GameObjectCommand {
public:

	explicit MoveCommand(GameObject* pGameObject);
	//don't make own destructor if not necessairy!

	void Execute() override; //implement code from the moveComponent (is deleted now)

	//don't cache gameObject again, it'a already saved in parent class
};




class SprayCommand : public GameObjectCommand {
public:

	explicit SprayCommand(GameObject* pGameObject);
	void Execute() override;
};



