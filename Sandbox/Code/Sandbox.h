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
        SceneManager::AddScene("sandbox");
        Scene* scene = SceneManager::GetScene("sandbox");

        Entity* cameraEntity = scene->CreateEntity("camera");
        mCameraComponent = cameraEntity->AddComponent<Camera>();
        cameraEntity->AddComponent<SceneCameraController>();
        mCameraComponent->SetProjectionType(Camera::ProjectionType::PERSPECTIVE);
        scene->SetMainCamera(mCameraComponent);

        Entity* boxEntity = scene->CreateEntity("box");
        boxEntity->AddComponent<MeshRenderer>();
        const auto cubeMesh = std::make_shared<Cube>();
        MeshFilter* meshFilter = boxEntity->GetComponent<MeshFilter>();
        meshFilter->SetMesh(cubeMesh);
        ResourceManager::AddTexture(std::make_shared<Texture>("Assets/Textures/container.jpg"));
        meshFilter->SetTexture(ResourceManager::GetTexture("Assets/Textures/container.jpg"));

        //Entity* boxEntity2 = scene->CreateEntity("box2");
        //boxEntity2->AddComponent<SpriteRenderer>();
        //boxEntity2->GetComponent<Sprite>()->LoadTexture("Assets/Textures/container.jpg");
        //boxEntity2->GetTransform().SetScale(100, 100, 1);
        //boxEntity2->GetTransform().SetPosition(Window::GetCenter().x, Window::GetCenter().y, 0);
    }

    void OnUpdate() override
    {

    }

private:
    Camera* mCameraComponent = nullptr;
};