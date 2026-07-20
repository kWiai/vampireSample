#pragma once

#include <string>

class Renderer;

class GameObject
{
public:

    GameObject();
    virtual ~GameObject();

    virtual void Update(float deltaTime);
    virtual void Render(Renderer& renderer);

    // Имя объекта
    void SetName(const std::string& name);
    const std::string& GetName() const;

    // Положение
    void SetPosition(float x, float y);
    float GetX() const;
    float GetY() const;

    // Размер
    void SetSize(float width, float height);
    float GetWidth() const;
    float GetHeight() const;

    // Активность
    void SetActive(bool active);
    bool IsActive() const;

protected:

    std::string m_Name;

    float m_X;
    float m_Y;

    float m_Width;
    float m_Height;

    bool m_IsActive;
};