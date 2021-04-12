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
        Scene* scene = SceneManager::GetScene("sandbox");

        Entity* cameraEntity = scene->CreateEntity("camera");
        mCameraComponent = cameraEntity->AddComponent<Camera>();
        mCameraController = cameraEntity->AddComponent<SceneCameraController>();
        mCameraComponent->SetProjectionType(Camera::ProjectionType::PERSPECTIVE);
        scene->SetMainCamera(mCameraComponent);

        Entity* boxEntity = scene->CreateEntity("box");
        Renderer* boxRenderer = boxEntity->AddComponent<MeshRenderer>();
        boxRenderer->GetMaterial().SetTexture(ResourceManager::GetTextureRef("Assets/Textures/container.jpg"));

        const auto cubeMesh = std::make_shared<Cube>();
        auto* meshFilter = boxEntity->GetComponent<MeshFilter>();
        meshFilter->SetMesh(cubeMesh);

        //Entity* boxEntity2 = scene->CreateEntity("box2");
        //Renderer* boxRenderer2 = boxEntity2->AddComponent<SpriteRenderer>();
        //boxRenderer2->GetMaterial().SetTexture(ResourceManager::GetTextureRef("Assets/Textures/container.jpg"));
        //boxEntity2->GetTransform().SetScale(100, 100, 1);
        //boxEntity2->GetTransform().SetPosition(Window::GetCenter().x, Window::GetCenter().y, 0);
        //mCameraController->SetPanSpeed(1000.0f);
    }

    void OnUpdate() override
    {

    }

private:
    Camera* mCameraComponent = nullptr;
    SceneCameraController* mCameraController = nullptr;
};