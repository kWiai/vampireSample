#pragma once

#include "Component.h"
#include "Camera.h"

class CameraComponent : public Component
{
public:

    CameraComponent();
    ~CameraComponent() override;

    void Update(float deltaTime) override;

    Camera& GetCamera();

    const Camera& GetCamera() const;

private:

    Camera m_Camera;
};