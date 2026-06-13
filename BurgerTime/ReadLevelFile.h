//
// Created by yasmi on 5/31/2026.
//

#ifndef MINIGIN_READLEVELFILE_H
#define MINIGIN_READLEVELFILE_H
#include <string>
#include "Scene.h"

    static const std::string spritePathShortTile {"shortTile.png"};
    static const std::string spritePathLongTile{"longTile.png"};
    static const std::string spritePathBasket{"basket.png"};
    static const std::string spritePathLongLadder{"longLadder.png"};
   static const std::string spritePathShortLadder{"shortLadder.png"};


class ReadLevelFile {
public:
    ReadLevelFile() = default;
    static void LoadlevelFromFile(dae::Scene& scene, const std::string& fileName);



private:

    enum class TileType { //each should be a gamobject, with spriterendered, and a collisionComponent (trigger)
        shortTile, //=0
        longTile,
        shortLadder, //trigger
        longLadder,  //trigger
        basket //=4
    };                          //burger parts need a trigger collider, to check if touching layers, but still need to fall through, SO NO NORMAL COLLIDERS

    struct Tile
    {
        TileType type;
        float posX;
        float posY;
    };

};


#endif //MINIGIN_READLEVELFILE_H
