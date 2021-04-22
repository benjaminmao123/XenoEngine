#pragma once

#include <Xeno.h>
#include <memory>
#include <iostream>

using namespace std;

class Sandbox : public Application
{
public:
    explicit Sandbox(Window::WindowProperties props) :
        Application(std::move(props))
    { }

protected:
    void OnRun() override
    {
        const Texture::TextureProperties containerTextureProps = 
        {
            "Assets/Textures/container.jpg",
            0, 0,
            GL_RGB, GL_RGB
        };
        ResourceManager::AddTexture(std::make_shared<Texture>(containerTextureProps));

        SceneManager::AddScene("sandbox");
        mScene = SceneManager::GetScene("sandbox");

        TestOrthographic();
        //TestPerspective();
    }

    void OnUpdate() override
    {
        if (Input::GetKeyDown(Input::KeyCode::X))
        {
            Application::GetGameWindow().ConstructWindow();
        }
    }

private:
    void TestOrthographic()
    {
        Entity* cameraEntity = mScene->CreateEntity("camera");
        mCameraComponent = cameraEntity->AddComponent<Camera>();
        mCameraController = cameraEntity->AddComponent<SceneCameraController>();
        mCameraComponent->SetProjectionType(Camera::ProjectionType::ORTHOGRAPHIC);
        mCameraController->SetPanSpeed(1000.0f);
        mScene->SetMainCamera(mCameraComponent);

        Entity* boxEntity = mScene->CreateEntity("box");
        Renderer* boxRenderer = boxEntity->AddComponent<SpriteRenderer>();
        boxRenderer->GetMaterial().SetTexture(ResourceManager::GetTextureRef("Assets/Textures/container.jpg"));

        boxEntity->GetTransform().SetScale(100, 100, 1);
        boxEntity->GetTransform().SetPosition(GetGameWindow().GetCenter().x, GetGameWindow().GetCenter().y, 0);
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