#include "pch.h"
#include "Renderer/Renderer.h"

std::vector<float> Xeno::Renderer::mQuad;
std::vector<uint32_t> Xeno::Renderer::mIndices;

void Xeno::Renderer::DrawQuad(const glm::vec2& position, const SDL_Color& color)
{
    GetShader().Bind();
    GetVAO().Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Xeno::Renderer::DrawQuad()
{
    GetShader().Bind();
    GetVAO().Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Xeno::Renderer::Init()
{
    //mQuad =
    //{   //position          //color
    //     0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // top right
    //     0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom right
    //    -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // bottom left
    //    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f  // top left
    //};

    //mQuad = 
    //{
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f   // top left 
    //};

    mQuad =
    {
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

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
    
    //GetEBO().SetIndicesNew(&mIndices[0], mIndices.size(), GL_STATIC_DRAW);

    GetVAO().AddBuffer(&GetVBO(), nullptr);
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
