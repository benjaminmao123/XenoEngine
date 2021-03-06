#pragma once

#include <Xeno.h>
#include <memory>
#include <iostream>

using namespace std;

class Sandbox : public Application
{
public:
    explicit Sandbox(const Window::WindowProperties& props) :
        Application(props)
    { }

protected:
    void OnRun() override
    {
        ResourceManager::AddTexture(std::make_shared<Texture>("Assets/Textures/container.jpg"));

        SceneManager::AddScene("sandbox");
        mScene = SceneManager::GetScene("sandbox");

        TestOrthographic();
        //TestPerspective();
    }

    void OnUpdate() override
    {

    }

private:
    void TestOrthographic()
    {
        Entity* cameraEntity = mScene->CreateEntity("camera");
        mCameraComponent = cameraEntity->AddComponent<Camera>();
        mCameraController = cameraEntity->AddComponent<SceneCameraController>();
        mCameraComponent->SetProjectionType(Camera::ProjectionType::ORTHOGRAPHIC);
        mScene->SetMainCamera(mCameraComponent);

        Entity* boxEntity = mScene->CreateEntity("box");
        Renderer* boxRenderer = boxEntity->AddComponent<SpriteRenderer>();
        boxRenderer->GetMaterial().SetTexture(ResourceManager::GetTextureRef("Assets/Textures/container.jpg"));
        boxEntity->GetTransform().SetScale(100, 100, 1);
        boxEntity->GetTransform().SetPosition(Window::GetCenter().x, Window::GetCenter().y, 0);
        mCameraController->SetPanSpeed(1000.0f);
    }

    void TestPerspective()
    {
        Entity* cameraEntity = mScene->CreateEntity("camera");
        mCameraComponent = cameraEntity->AddComponent<Camera>();
        mCameraController = cameraEntity->AddComponent<SceneCameraController>();
        mCameraComponent->SetProjectionType(Camera::ProjectionType::PERSPECTIVE);
        mScene->SetMainCamera(mCameraComponent);

        Entity* boxEntity = mScene->CreateEntity("box");
        Renderer* boxRenderer = boxEntity->AddComponent<MeshRenderer>();
        boxRenderer->GetMaterial().SetTexture(ResourceManager::GetTextureRef("Assets/Textures/container.jpg"));

        const auto cubeMesh = std::make_shared<Cube>();
        auto* meshFilter = boxEntity->GetComponent<MeshFilter>();
        meshFilter->SetMesh(cubeMesh);
    }

    Camera* mCameraComponent = nullptr;
    SceneCameraController* mCameraController = nullptr;
    Scene* mScene = nullptr;
};