#pragma once

#include <Xeno.h>
#include <string>
#include <iostream>

using namespace std;

class Sandbox : public Application
{
public:
    explicit Sandbox(const Window::WindowProperties& props) :
        Application(props),
        mTransformComponent(nullptr)
    {
        mTransformComponent.SetScale(100, 100, 1);
        mTransformComponent.SetPosition(Window::GetCenter().x,
                                        Window::GetCenter().y,
                                        0);
    }

protected:
    void OnRun() override
    {
        SceneManager::AddScene("sandbox");
        Scene* scene = SceneManager::GetScene("sandbox");

        Entity* cameraEntity = scene->CreateEntity("camera");
        mCameraComponent = cameraEntity->AddComponent<CameraComponent>();
        mCameraComponent->SetProjectionType(CameraComponent::ProjectionType::ORTHOGRAPHIC);
    }

    void OnUpdate() override
    {
        if (Input::GetKey(SDL_SCANCODE_W))
            mCameraComponent->GetTransform().Translate(0, -mCameraPanSpeed * Time::GetDeltaTime(), 0);
        if (Input::GetKey(SDL_SCANCODE_S))
            mCameraComponent->GetTransform().Translate(0, mCameraPanSpeed * Time::GetDeltaTime(), 0);
        if (Input::GetKey(SDL_SCANCODE_A))
            mCameraComponent->GetTransform().Translate(-mCameraPanSpeed * Time::GetDeltaTime(), 0, 0);
        if (Input::GetKey(SDL_SCANCODE_D))
            mCameraComponent->GetTransform().Translate(mCameraPanSpeed * Time::GetDeltaTime(), 0, 0);

        Renderer::DrawQuad(mTransformComponent, *mCameraComponent, Color::Green().ToFloat());
    }

private:
    CameraComponent* mCameraComponent = nullptr;
    TransformComponent mTransformComponent;
    float mCameraPanSpeed = 1000.0f;
};