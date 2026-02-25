#pragma once
#include <string>
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <SDL3/SDL.h>

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
	class TextComponent final : public Component
	{
	public:
		void Update() override;
		void Render() override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		void SetColor(const SDL_Color& color);

		TextComponent(GameObject* pGameObject, const std::string& text, std::shared_ptr<Font> font, int id, const SDL_Color& color = { 255, 255, 255, 255 });
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		Transform m_transform{};
		std::shared_ptr<Font> m_font{};

		std::shared_ptr<Texture2D> m_textTexture{};
	};
}
