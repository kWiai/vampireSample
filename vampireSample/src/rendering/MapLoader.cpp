#include "MapLoader.h"

#include <fstream>

#include "TileMap.h"

bool MapLoader::Load(
    const std::string& filename,
    TileMap& map)
{
    std::ifstream file(filename);

    if (!file.is_open()) 
    {
        return false;
    }

    int width;
    int height;

    file >> width >> height;

    map.Create(width, height);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int id;

            file >> id;

            map.SetTile(x, y, id);
        }
    }

    return true;
}