#pragma once

#include <string>

class TileMap;

class MapLoader
{
public:

    static bool Load(
        const std::string& filename,
        TileMap& map);
};