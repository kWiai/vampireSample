#include "ResourceManager.h"

#include "Texture2D.h"

std::unordered_map<
    std::wstring,
    std::shared_ptr<Texture2D>>
ResourceManager::m_Textures;

std::shared_ptr<Texture2D>
ResourceManager::LoadTexture(
    const std::wstring& filePath)
{
    auto it = m_Textures.find(filePath);

    if (it != m_Textures.end())
    {
        return it->second;
    }

    auto texture =
        std::make_shared<Texture2D>(filePath);

    if (!texture->IsLoaded())
    {
        return nullptr;
    }

    m_Textures[filePath] = texture;

    return texture;
}

void ResourceManager::Clear()
{
    m_Textures.clear();
}