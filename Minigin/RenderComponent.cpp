#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Texture2D.h"

namespace dae {

	void RenderComponent::Render()
	{

		if (m_texture)	//draws game objects who don't have components
		{
			//const auto& pos = m_transform.GetPosition();
			const auto& pos = GetOwner()->GetWorldPosition();
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		}

	}

	void RenderComponent::Update(){ };

	void RenderComponent::SetTexture(const std::string& filename)
	{
		m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	}

	void RenderComponent::SetTexture2D(std::shared_ptr<Texture2D> texture)
	{
		m_texture = texture;
	}

	glm::vec2 RenderComponent::GetTextureSize() const {
		return m_texture->GetSize();
	}

	void RenderComponent::SetPosition(float x, float y) //only for render and not gameObject -> doesn't always need to be drawn/need a pos
	{
		m_transform.SetPosition(x, y, 0.0f);
		currentPosition = {x,y};
		GetOwner()->SetLocalPosition(glm::vec3{ x, y,0 });
	}

	//make set scale function?
}
