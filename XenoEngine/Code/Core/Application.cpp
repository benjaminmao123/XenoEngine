#include "pch.h"
#include "Core/Application.h"
#include "Core/Logger.h"

#include <SDL2/SDL.h>

Xeno::Application::Application(const Window::WindowProperties& props) :
    mWindow(props)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        XN_CORE_ERROR(SDL_GetError());

        throw std::runtime_error("SDL failed to initialize.");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

Xeno::Application::~Application()
{
    SDL_Quit();
}

std::string ParseFile(const std::string& path)
{
    std::ifstream ifs(path);

    if (!ifs.is_open())
    {
        XN_CORE_ERROR("Failed to open file: {0}", path);

        return std::string();
    }

    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));

    return content;
}

void Xeno::Application::Run()
{
    if (!mIsRunning)
    {
        Create();

        while (mIsRunning)
        {
            mWindow.Clear(0, 0, 0, 255);
            
            PollEvents();

            //const uint32_t shaderProgram = glCreateProgram();

            //std::string vertex = ParseFile("Assets/Shaders/vertex.glsl");
            //std::string frag = ParseFile("Assets/Shaders/frag.glsl");

            //const char* vertexShaderSource = vertex.c_str();
            //const char* fragmentShaderSource = frag.c_str();

            //const uint32_t vertexShader = glCreateShader((GLenum)Shader::ShaderType::VERTEX);
            //glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
            //glCompileShader(vertexShader);

            //glAttachShader(shaderProgram, vertexShader);
            //glLinkProgram(shaderProgram);

            //glDeleteShader(vertexShader);

            //const uint32_t fragmentShader = glCreateShader((GLenum)Shader::ShaderType::FRAGMENT);
            //glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
            //glCompileShader(fragmentShader);

            //glAttachShader(shaderProgram, fragmentShader);
            //glLinkProgram(shaderProgram);

            //glDeleteShader(fragmentShader);

            float vertices[] = {
                -0.5f, -0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                 0.0f,  0.5f, 0.0f  
            };

            //unsigned int VBO, VAO;
            //glGenVertexArrays(1, &VAO);
            //glGenBuffers(1, &VBO);

            //glBindVertexArray(VAO);

            //glBindBuffer(GL_ARRAY_BUFFER, VBO);
            //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            //glEnableVertexAttribArray(0);

            //glBindBuffer(GL_ARRAY_BUFFER, 0);

            //glBindVertexArray(0);

            //glUseProgram(shaderProgram);
            //glBindVertexArray(VAO);
            //glDrawArrays(GL_TRIANGLES, 0, 3);

            //Shader shader;
            //shader.AddShader({ "Assets/Shaders/vertex.glsl", Shader::ShaderType::VERTEX });
            //shader.AddShader({ "Assets/Shaders/frag.glsl", Shader::ShaderType::FRAGMENT });

            //VertexArray VAO;
            //VertexBuffer VBO;

            //VAO.Bind();

            //VBO.SetDataNew(vertices, sizeof(vertices));
            //VBO.PushElement({ "positions", 3, GL_FLOAT, sizeof(float) });

            //VAO.AddBuffer(VBO);

            //shader.Bind();
            //glUseProgram(shaderProgram);
            //glDrawArrays(GL_TRIANGLES, 0, 3);
            //Renderer::DrawQuad(glm::vec2(0, 0), SDL_Color(0, 0, 0));
            Renderer::DrawQuad();

            Update();
        }
    }
}

void Xeno::Application::PollEvents()
{
    while (SDL_PollEvent(&mEvent))
    {
        mInput.ProcessEvents(mEvent);

        switch (mEvent.type)
        {
        case SDL_QUIT:
            OnExit();
            break;
        default:
            break;
        }
    }
}

void Xeno::Application::OnExit()
{
    mIsRunning = false;
}

void Xeno::Application::OnCreate()
{ }

void Xeno::Application::OnUpdate()
{ }

void Xeno::Application::Create()
{
    if (!mWindow.ConstructWindow())
    {
        XN_CORE_ERROR("Failed to construct window.");

        return;
    }

    mRenderer.Init();

    OnCreate();

    mIsRunning = true;
}

void Xeno::Application::Update()
{
    mTime.Update();
    mInput.Update();
    OnUpdate();
    mWindow.Update();
}
