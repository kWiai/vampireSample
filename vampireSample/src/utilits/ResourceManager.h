#pragma once

#include <memory>
#include <string>
#include <unordered_map>

class Texture2D;

class ResourceManager
{
public:

    static std::shared_ptr<Texture2D> LoadTexture(
        const std::wstring& filePath);

    static void Clear();

private:

    static std::unordered_map<
        std::wstring,
        std::shared_ptr<Texture2D>> m_Textures;
};