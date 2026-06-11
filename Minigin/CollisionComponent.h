//
// Created by yasmi on 6/9/2026.
//

#ifndef MINIGIN_COLLISIONCOMPONENT_H
#define MINIGIN_COLLISIONCOMPONENT_H


#include "Component.h"
#include "GameObject.h"


class CollisionComponent final : public dae::Component
{
public:
    CollisionComponent(dae::GameObject* pGameObject, bool isObStatic, bool isDebugDrawingOn = false, int id = 0);

     void Update() override; //check collision     //scenemanager, get curr->Scene::GetVisibleObjects()
     void Render() override; //draw debug!

    enum class CollisionType {
        OnEnter,
        OnStay,
        OnExit
    };

    enum class Alignment {
        Top,
        Bottom,
        Left,
        Right,
        Center
    };

    struct Rect {
        float x, y, width, height;
    };
    
    //also set size + alignment (top/bottom/left/right/center?)

    void SetCollisionBox(float width, float height, Alignment align = Alignment::Center);
    void SetFunction(std::function<void(CollisionComponent *)> CollisionLogic, CollisionType type);

    [[nodiscard]]Rect GetRect();
    [[nodiscard]] std::string  GetOwnerTag();

    //set function to check + pick which function   //so owner calls child and passes this!!
    //-> inside function should check for tag! (owner responsibility)



private:
    static bool IsOverlapping(const Rect& a, const Rect& b); //give in par for 2 rectangles.
    //is there any way to optimize this??

    bool isStatic;
    bool m_IsDebugDrawingOn;

    float m_Width{0.f};
    float m_Height{0.f};
    Alignment m_Alignment {Alignment::Center};

    std::unordered_map<CollisionType, std::function<void(CollisionComponent*)>> m_Callbacks;

    // bool m_HasEntered = false;
    // bool m_HasExited = false;

    std::function<void(CollisionComponent*)> CollisionFunction;
    std::vector<CollisionComponent*> m_PreviousOverlaps;
};


#endif //MINIGIN_COLLISIONCOMPONENT_H
