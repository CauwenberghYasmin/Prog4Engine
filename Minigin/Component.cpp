#include "Component.h"

namespace dae
{ 

Component::Component(float id):
	m_IdNumber{ id }
{
}


float Component::GetID()
{
	return m_IdNumber;
}


}