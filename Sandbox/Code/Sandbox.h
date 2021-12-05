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
        const Texture::TextureProperties containerDiffuse = 
        {
            "Assets/Textures/container2.png",
            Material::TextureMap::DIFFUSE,
            0, 0,
            GL_RGBA, GL_RGBA,
            GL_UNSIGNED_BYTE,
            GL_REPEAT, GL_REPEAT,
            GL_LINEAR, GL_LINEAR
        };

        ResourceManager::AddTexture(std::make_shared<Texture>(containerDiffuse, true));

        const Texture::TextureProperties containerSpecular =
        {
            "Assets/Textures/container2_specular.png",
            Material::TextureMap::SPECULAR,
            0, 0,
            GL_RGBA, GL_RGBA,
            GL_UNSIGNED_BYTE,
            GL_REPEAT, GL_REPEAT,
            GL_LINEAR, GL_LINEAR
        };

        ResourceManager::AddTexture(std::make_shared<Texture>(containerSpecular, true));

        const Texture::TextureProperties container =
        {
            "Assets/Textures/container.jpg",
            Material::TextureMap::NONE,
            0, 0,
            GL_RGB, GL_RGB
        };

        ResourceManager::AddTexture(std::make_shared<Texture>(container));

        SceneManager::AddScene("sandbox");
        mScene = SceneManager::GetScene("sandbox");

        //TestOrthographic();
        TestPerspective();
    }

    void OnUpdate() override
    {
        if (Input::GetKey(KeyCode::ESCAPE))
            Quit();
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
        boxRenderer->GetMaterial().SetTexture(ResourceManager::GetTexture("Assets/Textures/container.jpg"));

        boxEntity->GetTransform().SetScale(100, 100, 1);
        boxEntity->GetTransform().SetPosition(GetGameWindow().GetCenter().x, GetGameWindow().GetCenter().y, 0);
    }

    void TestPerspective()
    {
        SceneRenderer::SetClearColor(Color(0.1f, 0.1f, 0.1f));

        Input::SetCursorLockState(Input::CursorLockState::LOCKED);

        Entity* cameraEntity = mScene->CreateEntity("camera");
        mCameraComponent = cameraEntity->AddComponent<Camera>();
        mCameraController = cameraEntity->AddComponent<SceneCameraController>();
        mCameraController->SetSensitivity(30.0f);
        mCameraComponent->SetProjectionType(Camera::ProjectionType::PERSPECTIVE);
        mScene->SetMainCamera(mCameraComponent);
        mSpotLight = cameraEntity->AddComponent<Light>(Light::LightType::SPOT);

        //auto* planeEntity = mScene->CreateEntity("plane");
        //planeEntity->GetTransform().SetRotationEuler(270.0f, 0.0f, 0.0f);
        //planeEntity->GetTransform().SetScale(10.0f, 10.0f, 10.0f);
        //auto* planeRenderer = planeEntity->AddComponent<MeshRenderer>();

        //const auto planeMesh = std::make_shared<Plane>();
        //auto* planeMeshFilter = planeEntity->GetComponent<MeshFilter>();
        //planeMeshFilter->SetMesh(planeMesh);

        auto* boxEntity = mScene->CreateEntity("box");
        boxEntity->GetTransform().SetPosition(0.0f, 1.1f, 0.0f);
        auto* boxRenderer = boxEntity->AddComponent<MeshRenderer>();
        boxRenderer->GetMaterial().SetDiffuseMap(ResourceManager::GetTexture("Assets/Textures/container2.png"));
        boxRenderer->GetMaterial().SetSpecularMap(ResourceManager::GetTexture("Assets/Textures/container2_specular.png"));

        const auto cubeMesh = std::make_shared<Cube>();
        auto* meshFilter = boxEntity->GetComponent<MeshFilter>();
        meshFilter->SetMesh(cubeMesh);

        auto* directionalLightEntity = mScene->CreateEntity("directional light");
        mDirectionalLight = directionalLightEntity->AddComponent<Light>(Light::LightType::DIRECTIONAL);
        mDirectionalLight->SetAmbient(0.5f, 0.5f, 0.5f);
        directionalLightEntity->GetTransform().SetPosition(0.0f, 10.0f, 0.0f);
        directionalLightEntity->GetTransform().SetRotationEuler(70.0f, 0.0f, 0.0f);
    }

    Camera* mCameraComponent = nullptr;
    SceneCameraController* mCameraController = nullptr;
    Scene* mScene = nullptr;
    Light* mDirectionalLight = nullptr;
    Light* mSpotLight = nullptr;
    Light* mPointLight = nullptr;
};