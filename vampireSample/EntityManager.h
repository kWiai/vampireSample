#pragma once

#include <memory>
#include <string>

class GameObject;

class EntityManager
{
public:

    EntityManager();
    ~EntityManager();

    std::unique_ptr<GameObject> Create(
        const std::string& entityName);
};