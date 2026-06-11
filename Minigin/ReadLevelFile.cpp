//
// Created by yasmi on 5/31/2026.
//

#include "ReadLevelFile.h"
#include "GameObject.h"
#include "renderComponent.h"
#include "CollisionComponent.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <type_traits>

//should read/parse file
//then create instances of each tile and add them so the scene, (pos + colliders)

//RESON WORKING LIKE THIS
//we don't really have a grid/tiles we need to place, merely some minor thigns in the scene, so this solution works best

void ReadLevelFile::LoadlevelFromFile(dae::Scene& scene, const std::string& fileName)
{
    //see prog 3 referen e
    std::ifstream input;
    input.open(fileName, std::ios::binary);
    std::string line{};
    while (std::getline(input, line))
    {
        if (line[0] == '#' ||line.empty()) // the # are just to write comments in the doc
        {
            continue;
        }
        else {
            Tile tile {};
            auto command = line[0];
            std::string filePath {};
            auto tileObject = std::make_unique<dae::GameObject>();

            switch (command) {
                case '0': //shorttile
                    tile.type = TileType::shortTile;
                    filePath = spritePathShortTile;
                    tileObject->Tag = "Tile";
                    break;
                case '1'://longtile
                    tile.type = TileType::longTile;
                    filePath = spritePathLongTile;
                    tileObject->Tag = "Tile";
                    break;
                case '2'://shortladder
                    tile.type = TileType::shortLadder;
                    filePath = spritePathShortLadder;
                    tileObject->Tag = "Ladder";
                    break;
                case '3'://longladder
                    tile.type = TileType::longLadder;
                    filePath = spritePathLongLadder;
                    tileObject->Tag = "Ladder";
                    break;
                case '4'://basket
                    tile.type = TileType::basket;
                    filePath = spritePathBasket;
                    break;
                //default:
                //    tile.type = TileType::shortTile;
                //    filePath = spritePathShortTile;
                }

            std::istringstream iss(line);
            float x, y;
            std::string a;
            if (!(iss >> a >> x >> y))
            {
                std::cout << "something went wrong...?";
            }
            else
            {
                tile.posX = x;
                tile.posY = y;
            }

            //gave tag in switch case!
            auto sprite = std::make_unique<dae::RenderComponent>(tileObject.get());
            sprite->SetTexture(filePath);
            sprite->SetPosition(tile.posX, tile.posY);
            tileObject->AddComponent(std::move(sprite));
            tileObject->AddComponent(std::make_unique<CollisionComponent>(tileObject.get(), true));
            //dont add tile logic here? (on collision function)
            scene.Add(std::move(tileObject));
        }
    }
}
//HOW TO ADD EACH OBJECT

// auto scene02 = std::make_unique<dae::GameObject>();
// auto logo = std::make_unique<dae::RenderComponent>(scene02.get());
// logo->SetTexture("logo.png");
// logo->SetPosition(358, 180);
// scene02->AddComponent(std::move(logo));
//ADD COLLISION COMPONENT!!!
// scene.Add(std::move(scene02));