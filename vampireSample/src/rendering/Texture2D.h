#pragma once

#include <windows.h>
#include <gdiplus.h>

#include <string>

#pragma comment(lib, "gdiplus.lib")

using namespace Gdiplus;

class Texture2D
{
public:

    explicit Texture2D(const std::wstring& filePath);

    ~Texture2D();

    Image* GetImage() const;

    bool IsLoaded() const;

private:

    Image* m_Image;
};