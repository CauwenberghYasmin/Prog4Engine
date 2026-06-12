//
// Created by yasmi on 6/9/2026.
//

#include "CollisionComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Renderer.h"
#include <SDL3/SDL.h>

#include "renderComponent.h"


CollisionComponent::CollisionComponent(dae::GameObject* pGameObject, bool isObStatic, bool isDebugDrawingOn, int id)
    :Component(pGameObject, id), isStatic(isObStatic), m_IsDebugDrawingOn(isDebugDrawingOn)
{
    //safe here and then pass so no double lookup 

    m_Width = GetOwner()->GetComponent<dae::RenderComponent>()->GetTextureSize().x;
    m_Height = GetOwner()->GetComponent<dae::RenderComponent>()->GetTextureSize().y;
}

void CollisionComponent::Update() //check collision     //scenemanager, get curr->Scene::GetVisibleObjects()
{

    if (isStatic) return; //should only check moving objects, or special objects that have logic (icecream, bnus points)


    auto* scene = dae::SceneManager::GetInstance().GetCurrentScene();
    auto possOverlap = scene->GetCollisionObjects();   // returns std::vector<CollisionComponent*>

    const Rect myRect = GetRect();

    std::vector<CollisionComponent*> currentOverlaps; //is there a way to optimize this???

    for (auto* gameObj : possOverlap)
    {
        auto compOther = gameObj->GetComponent<CollisionComponent>();

        if (compOther == this) continue;

        if (IsOverlapping(myRect, compOther->GetRect()))
        {
            currentOverlaps.emplace_back(compOther); //false error

            const bool wasOverlappingLastFrame =
                std::find(m_PreviousOverlaps.begin(), m_PreviousOverlaps.end(), compOther)
                != m_PreviousOverlaps.end();


            if (!wasOverlappingLastFrame) //ON ENTER!!!
            {
                if (auto it = m_Callbacks.find(CollisionType::OnEnter);
                    it != m_Callbacks.end())
                    it->second(compOther);
            }
            else //ON STAY
            {
                if (auto it = m_Callbacks.find(CollisionType::OnStay);
                    it != m_Callbacks.end())
                    it->second(compOther);
            }
        }
    }

    for (CollisionComponent* prev : m_PreviousOverlaps) //ON EXIT
    {
        const bool stillOverlapping =
            std::find(currentOverlaps.begin(), currentOverlaps.end(), prev)
            != currentOverlaps.end();

        if (!stillOverlapping)
        {
            if (auto it = m_Callbacks.find(CollisionType::OnExit);
                it != m_Callbacks.end())
                it->second(prev);
        }
    }

    m_PreviousOverlaps = std::move(currentOverlaps); //no need to erase since replace :D (should optimize this!!!)
}

CollisionComponent::Rect CollisionComponent::GetRect() {

    const glm::vec2 pos = GetOwner()->GetWorldPosition();
    const glm::vec2 size  = GetOwner()->GetComponent<dae::RenderComponent>()->GetTextureSize();

    float offsetX = 0.f;
    float offsetY = 0.f;

    switch (m_Alignment)
    {
        case Alignment::Center:
            offsetX = (size.x - m_Width) * 0.5f;
            offsetY = (size.y - m_Height) * 0.5f;
            break;

        case Alignment::Top:
            offsetX = (size.x - m_Width) * 0.5f;
            offsetY = 0.f;
            break;

        case Alignment::Bottom:
            offsetX = (size.x - m_Width) * 0.5f;
            offsetY = size.y - m_Height;
            break;

        case Alignment::Left:
            offsetX = 0.f;
            offsetY = (size.y - m_Height) * 0.5f;
            break;

        case Alignment::Right:
            offsetX = size.x - m_Width;
            offsetY = (size.y - m_Height) * 0.5f;
            break;
    }

    return { pos.x + offsetX, pos.y + offsetY, m_Width, m_Height };
}



void CollisionComponent::SetCollisionBox(float width, float height, Alignment align)
{
    m_Width  = width;
    m_Height = height;
    m_Alignment  = align;
}

void CollisionComponent::Render()
{
    if (!m_IsDebugDrawingOn) return;

    const Rect rect = GetRect();
    SDL_Renderer* sdlRenderer = dae::Renderer::GetInstance().GetSDLRenderer();
    SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);

    const SDL_FRect rectangle{ rect.x, rect.y, rect.width, rect.height };
    SDL_RenderRect(sdlRenderer, &rectangle);
}

std::string CollisionComponent::GetOwnerTag()
{
    return GetOwner()->Tag; //never needs own, its for the others!
}


void CollisionComponent::SetFunction( std::function<void(CollisionComponent*)> callback, CollisionType type)
{
    m_Callbacks[type] = std::move(callback);
}


bool CollisionComponent::IsOverlapping(const Rect& a, const Rect& b)
{
    return a.x         < b.x + b.width
        && a.x + a.width  > b.x
        && a.y         < b.y + b.height
        && a.y + a.height > b.y;
}