#include "CameraComponent.h"
#include "GameObject.h"

CameraComponent::CameraComponent()
{

}

CameraComponent::~CameraComponent()
{

}
void CameraComponent::Update(float deltaTime)
{
}

Camera& CameraComponent::GetCamera()
{
    return m_Camera;
}

const Camera& CameraComponent::GetCamera() const
{
    return m_Camera;
}