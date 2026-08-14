#include "src/rendering/Texture2D.h"

Texture2D::Texture2D(const std::wstring& filePath)
{
    m_Image = new Image(filePath.c_str());
}

Texture2D::~Texture2D()
{
    delete m_Image;
}

Image* Texture2D::GetImage() const
{
    return m_Image;
}

bool Texture2D::IsLoaded() const
{
    return m_Image &&
        m_Image->GetLastStatus() == Ok;
}