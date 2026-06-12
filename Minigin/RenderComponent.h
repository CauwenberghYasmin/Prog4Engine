#pragma once
#include "Component.h"
#include "Transform.h"
#include <string>
#include <memory>


namespace dae
{
    class Texture2D;
    class GameObject;
    class RenderComponent final : public Component //can only render 1 tthing at a time!!
    {
    public:
        RenderComponent(GameObject* pGameObject, int id = 0):
            Component(pGameObject, id) {
        }
        ~RenderComponent() = default;

       
        // void Update() override;
        void Render() override;
        void Update() override;
        void SetTexture(const std::string& filename);
        void SetTexture2D(std::shared_ptr<Texture2D> texture); //for textComponent
        void SetPosition(float x, float y);
        glm::vec2 GetTextureSize() const;
        glm::vec2 currentPosition{};

        //recheck rule of 5
        RenderComponent(const RenderComponent&) = delete;
        RenderComponent& operator=(const RenderComponent&) = delete;


        bool m_IsRendering{true}; //public!
    private:
        Transform m_transform{};
        std::shared_ptr<Texture2D> m_texture{};

    };

}