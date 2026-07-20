#include "GameObject.h"
#include "Render.h"

GameObject::GameObject()
{
    m_Name = "GameObject";

    m_X = 0.0f;
    m_Y = 0.0f;

    m_Width = 0.0f;
    m_Height = 0.0f;

    m_IsActive = true;
}

GameObject::~GameObject()
{

}

void GameObject::Update(float deltaTime)
{

}

void GameObject::Render(Renderer& renderer)
{

}

void GameObject::SetName(const std::string& name)
{
    m_Name = name;
}

const std::string& GameObject::GetName() const
{
    return m_Name;
}

void GameObject::SetPosition(float x, float y)
{
    m_X = x;
    m_Y = y;
}

float GameObject::GetX() const
{
    return m_X;
}

float GameObject::GetY() const
{
    return m_Y;
}

void GameObject::SetSize(float width, float height)
{
    m_Width = width;
    m_Height = height;
}

float GameObject::GetWidth() const
{
    return m_Width;
}

float GameObject::GetHeight() const
{
    return m_Height;
}

void GameObject::SetActive(bool active)
{
    m_IsActive = active;
}

bool GameObject::IsActive() const
{
    return m_IsActive;
}