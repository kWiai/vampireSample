#pragma once

#include <string>

#include "EntityDefinition.h"

class EntityLoader
{
public:

    static bool Load(
        const std::string& filePath,
        EntityDefinition& definition);
};