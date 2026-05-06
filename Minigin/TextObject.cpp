#include <stdexcept>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Component.h"
#include "GameObject.h"
#include "RenderComponent.h"



dae::TextComponent::TextComponent(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font, int id, const SDL_Color& color) //add render component id?
	: Component(pGameObject, id),
	m_needsUpdate(true), m_text(text), m_color(color), m_font(std::move(font)), m_textTexture(nullptr), m_RenderID(0)
{	

}


dae::TextComponent::TextComponent(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font, int id, int renderID, const SDL_Color& color) //add render component id?
	: Component(pGameObject, id),
	m_needsUpdate(true), m_text(text), m_color(color), m_font(std::move(font)), m_textTexture(nullptr), m_RenderID(renderID)
{	
}

void dae::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_DestroySurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() //need reference to render component
{
	if (m_RenderID == 0 && m_RendererFound ==false)
	{
		m_pRenderComponent = (GetOwner()->GetComponent<RenderComponent>());
		m_RendererFound = true;
	}
	if (m_RenderID != 0 && m_RendererFound == false)
	{
		m_pRenderComponent = (GetOwner()->GetComponent<RenderComponent>(m_RenderID));
		m_RendererFound = true;
	}

	m_pRenderComponent->SetPosition(m_transform.GetPosition().x, m_transform.GetPosition().y);
	m_pRenderComponent->SetTexture2D(m_textTexture);


}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetPosition(const float x, const float y)
{
	m_transform.SetPosition(x, y);
	GetOwner()->SetLocalPosition(glm::vec3{ x, y, 0 });
}

void dae::TextComponent::SetColor(const SDL_Color& color) 
{ 
	m_color = color; 
	m_needsUpdate = true; 
}


