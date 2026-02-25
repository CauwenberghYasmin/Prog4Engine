#include "Component.h"

namespace dae
{ 

Component::Component(GameObject* owner, int id):
	m_pOwner{owner}, m_IdNumber { id}
{
}


int Component::GetID()
{
	return m_IdNumber;
}


}