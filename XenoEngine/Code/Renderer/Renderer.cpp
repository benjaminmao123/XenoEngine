#include "pch.h"
#include "Renderer/Renderer.h"
#include "Core/Window.h"

std::vector<float> Xeno::Renderer::mQuad;
std::vector<uint32_t> Xeno::Renderer::mIndices;

void Xeno::Renderer::DrawQuad(const TransformComponent& transform, 
                              const CameraComponent& camera, 
                              const SDL_Color& color)
{
    ////GetTexture().Bind();
    GetShader().Bind();
    GetVAO().Bind();
    const glm::mat4 mvp = camera.GetViewProjection() * transform.GetModelMatrix();
    //glm::mat4 mvp = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    //mvp = glm::translate(mvp, glm::vec3(0.5f, -0.5f, 0.0f));

    GetShader().SetMat4("uMVP", mvp);
    //GetShader().SetFloat4("uColor", 
    //                      glm::vec4(color.r / 255, 
    //                                color.g / 255, 
    //                                color.b / 255, 
    //                                color.a / 255));
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

    //GetShader().Bind();
    //GetVAO().Bind();
    //glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Xeno::Renderer::Init()
{
    //mQuad =
    //{
    //     // positions           // colors                   // texture coords
    //     0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 1.0f, // top right
    //     0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     1.0f, 0.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 0.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f, 1.0f,     0.0f, 1.0f  // top left 
    //};

    mQuad =
    {
        // positions          // colors           // texture coords
         1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
         1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
        -1.0f, -1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
    };

    //mQuad =
    //{
    //    // positions           // texture coords
    //    0.5f,  0.5f, 0.0f,     1.0f, 1.0f, // top right
    //    0.5f, -0.5f, 0.0f,     1.0f, 0.0f, // bottom right
    //   -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // bottom left
    //   -0.5f,  0.5f, 0.0f,     0.0f, 1.0f  // top left 
    //};

    //mQuad =
    //{
    //     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    //    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
    //     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    //};

    mIndices =
    {
        0, 1, 3,
        1, 2, 3
    };

    GetShader().AddShader({ "Assets/Shaders/vertex.glsl", Shader::ShaderType::VERTEX });
    GetShader().AddShader({ "Assets/Shaders/frag.glsl", Shader::ShaderType::FRAGMENT });

    GetVAO().Bind();

    GetVBO().SetDataNew(&mQuad[0], mQuad.size() * sizeof(float), GL_STATIC_DRAW);
    GetVBO().PushElement({ "aPosition", 3, GL_FLOAT, sizeof(float) });
    GetVBO().PushElement({ "aColor", 3, GL_FLOAT, sizeof(float) });
    GetVBO().PushElement({ "aTexCoords", 2, GL_FLOAT, sizeof(float) });

    GetEBO().SetIndicesNew(&mIndices[0], mIndices.size(), GL_STATIC_DRAW);

    GetVAO().AddBuffer(&GetVBO(), &GetEBO());

    GetTexture().LoadTextureFromFile("Assets/Textures/container.jpg");
}

Xeno::VertexArray& Xeno::Renderer::GetVAO()
{
    static VertexArray VAO;

    return VAO;
}

Xeno::VertexBuffer& Xeno::Renderer::GetVBO()
{
    static VertexBuffer VBO;

    return VBO;
}

Xeno::ElementBuffer& Xeno::Renderer::GetEBO()
{
    static ElementBuffer EBO;

    return EBO;
}

Xeno::Texture& Xeno::Renderer::GetTexture()
{
    static Texture texture;

    return texture;
}

Xeno::Shader& Xeno::Renderer::GetShader()
{
    static Shader shader;

    return shader;
}
