//
// Created by KiiroiSenko on 12/26/2023.
//

#include "IERenderer.h"
#include <glad/glad.h>
#include <iostream>


const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.xyz, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

IERenderer* IERenderer::initialize()
{
    IE_ASSERT_MSG(RendererInstance == nullptr, "Multiple InfEngine::Initialize() calls detected! Engine is already initialized!"); // Does not work in release build
    if (RendererInstance != nullptr)
    {
        return RendererInstance;
    }
    std::cout << "Initializing Renderer" << std::endl;

    // Make a new instance of the renderer
    RendererInstance = new IERenderer();

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return nullptr;
    }

    // Set OpenGL version (e.g., 3.3)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // Create a window
    RendererInstance->Window = SDL_CreateWindow("Infinity_Engine_renderer_It_01", 100, 100, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!RendererInstance->Window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        return nullptr;
    }

    // Create an OpenGL context associated with the window
    RendererInstance->GLContext = SDL_GL_CreateContext(RendererInstance->Window);

    // Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        SDL_Log("Failed to initialize GLAD");
        SDL_Quit();
        return nullptr;
    }

    glViewport(0, 0, 800, 600);

    // Shader compilation
    CompileShaders();

    GLuint VBO, EBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return RendererInstance;
}

void IERenderer::RenderFrame()
{

    // Rendering
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //float vertices[] = {
    //        // first triangle
    //        0.5f,  0.5f, 0.0f,  // top right
    //        0.5f, -0.5f, 0.0f,  // bottom right
    //        -0.5f,  0.5f, 0.0f,  // top left
    //        // second triangle
    //        0.5f, -0.5f, 0.0f,  // bottom right
    //        -0.5f, -0.5f, 0.0f,  // bottom left
    //        -0.5f,  0.5f, 0.0f   // top left
    //};

    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
           -0.5f, -0.5f, 0.0f,  // bottom left
           -0.5f,  0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);
    //glBindVertexArray(0);
    //glDrawArrays(GL_TRIANGLES, 0, 6);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


    // Swap buffers
    SDL_GL_SwapWindow(Window);
}

void IERenderer::CompileShaders()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    bool ShaderProcessingSucceeded = true;
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        ShaderProcessingSucceeded = false;
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);


    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        ShaderProcessingSucceeded = false;
    }

    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINK::FAILED\n" << infoLog << std::endl;
        ShaderProcessingSucceeded = false;
    }

    if (ShaderProcessingSucceeded)
    {
        std::cout << "Shaders successfully processed!" << std::endl;
        glUseProgram(shaderProgram);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void IERenderer::PollFrameInputs(std::queue<SDL_Event>& OutEvents)
{
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {
        OutEvents.push(Event);
    }
}

void IERenderer::ResizeRendererToWindow(int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}

void IERenderer::Destroy()
{
    // Clean up
    SDL_GL_DeleteContext(GLContext);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}


