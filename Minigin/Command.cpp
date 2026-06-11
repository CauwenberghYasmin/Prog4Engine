#include "Command.h"
#include "GameTime.h"
#include "GameObject.h"
#include <iostream>
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include <cassert>
#include "ObserverManager.h"
#include "SceneManager.h"
#include "Game.h"
#include "ServiceLocator.h"

namespace dae {



	//constructor base class -> derive from it an dcall the base constructor!
	GameObjectCommand::GameObjectCommand(GameObject* pGameObject) :
		m_GameObject{ pGameObject } 
	{
	}

	MoveCommand::MoveCommand(GameObject* pGameObject, Direction direction, float speed) :
		GameObjectCommand(pGameObject), m_Direction (direction), m_Speed(speed)
	{
	}

	SprayCommand::SprayCommand(GameObject* pGameObject) :
		GameObjectCommand(pGameObject)
	{
	}

	HealthCommand::HealthCommand(GameObject* pGameObject, int ChangeHealthAmount) :
		GameObjectCommand(pGameObject), m_AmountHealthChange (ChangeHealthAmount)
	{
		m_ObjectsHealthComponent = m_GameObject->GetComponent<HealthComponent>(); //cashing health component
	}


	ScoreCommand::ScoreCommand(GameObject* pGameObject, int ChangeScorePoints) :
		GameObjectCommand(pGameObject), m_AmountScoreChange(ChangeScorePoints)
	{
		m_ObjectsScoreComponent = m_GameObject->GetComponent<ScoreComponent>(); //cashing health component
	}


	void MoveCommand::Execute() //how to I pass the direction enum??
	{
		glm::vec3 displacementVector{ 0,0,0 };
		float deltaTime = dae::GameTime::GetInstance().GetDeltaTime();

		switch (m_Direction) //game only requires straight up, down, left and right. no circle movement behaviours!
		{
		case Direction::Left:
			displacementVector.x -= m_Speed * deltaTime; //look into normalized value * speed or smth
			break;
		case Direction::Right:
			displacementVector.x += m_Speed * deltaTime; //maybe use geometric algebra from class!!!
			break;
		case Direction::Up:
			displacementVector.y -= m_Speed * deltaTime;
			break;
		case Direction::Down:
			displacementVector.y += m_Speed * deltaTime;
			break;
		}

		m_GameObject->SetLocalPosition(m_GameObject->GetLocalPosition() + (displacementVector * deltaTime));
	}



	SetGameModeCommand::SetGameModeCommand( GameObject* pGameObject, Game* game, std::vector<std::pair<float, Game::GameMode>> modeMappings)
	: GameObjectCommand(pGameObject), m_Game(game), m_ModeMappings(std::move(modeMappings)) // Use std::move for efficiency
{
}

	void SetGameModeCommand::Execute()
	{
		const float currPosY {m_GameObject->GetLocalPosition().y};

		for (const auto& mapping : m_ModeMappings)
		{
			if ((currPosY - mapping.first) < 0.01) //check for error floats
			{
				m_Game->currGameMode = mapping.second;

				if (m_Game->currGameMode != Game::GameMode::single) {
					ServiceLocator::get_sound_system().PlaySound(1, 50);
				}
				if (m_Game->currGameMode != Game::GameMode::Coop) {
					ServiceLocator::get_sound_system().PlaySound(1, 50);
				}
				if (m_Game->currGameMode != Game::GameMode::VS) {
					ServiceLocator::get_sound_system().PlaySound(1, 50);
				}

				break;
			}
		}


		dae::SceneManager::GetInstance().SetScene("Level01");
	}


	ArrowMoveCommand::ArrowMoveCommand(GameObject* pGameObject, Direction direction, float space, int amount) :
		GameObjectCommand(pGameObject), m_Direction (direction), m_JumpBlocks(space), m_RowAmount(amount-1)
	{
		m_MinPosY = m_GameObject->GetLocalPosition().y;
		m_MaxPosY = m_GameObject->GetLocalPosition().y +( m_JumpBlocks * static_cast<float>(m_RowAmount));
	}

	void ArrowMoveCommand::Execute()
	{
		auto currentPosition = m_GameObject->GetLocalPosition();

		switch (m_Direction)
		{
			case Direction::Up:
			if (currentPosition.y != m_MinPosY)
			{
				m_GameObject->SetLocalPosition(glm::vec3(currentPosition.x, (currentPosition.y - m_JumpBlocks), 0.f));

			}
			else//roundabout
			{
				m_GameObject->SetLocalPosition(glm::vec3(currentPosition.x, (currentPosition.y + m_JumpBlocks * static_cast<float>(m_RowAmount)), 0.f));
			}
			break;
			case Direction::Down:
			if (currentPosition.y != m_MaxPosY)
			{
				m_GameObject->SetLocalPosition(glm::vec3(currentPosition.x, (currentPosition.y + m_JumpBlocks), 0.f));
			}
			else//roundabout
			{
				m_GameObject->SetLocalPosition(glm::vec3(currentPosition.x, (currentPosition.y - m_JumpBlocks * static_cast<float>(m_RowAmount)), 0.f));
			}
			break;
		}
	}





	void HealthCommand::Execute()
	{
		assert(m_ObjectsHealthComponent != nullptr && "Healthcomponent = nullptr command");

		//TEMP FOR TESTING, DELETE
		//dae::SceneManager::GetInstance().SetScene("Level03");

		m_ObjectsHealthComponent->ChangeHealth(m_AmountHealthChange); //inside here observer!
	}



	void ScoreCommand::Execute()
	{
		assert(m_ObjectsScoreComponent != nullptr && "Healthcomponent was a nullpointer in the command execute.");
		//m_ObjectsScoreComponent->AddScorePoints(m_AmountScoreChange);
		m_AmountScoreChange++;
	}



	void SprayCommand::Execute()
	{
		//GetGameActor()->Spray(); //put in cpp file so can include the h file

			//can spray in direction last looked (up/down/left/right)
			//show sparkle effect
			//look if sound effect..?
			//make somewhere a collision system so that the enemies know what they are hit
			//make counter of amount of sprays go down (event system?)
	}

}