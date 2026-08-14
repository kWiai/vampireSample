#pragma once

#include "src/core/Component.h"
#include "src/rendering/Camera.h"

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