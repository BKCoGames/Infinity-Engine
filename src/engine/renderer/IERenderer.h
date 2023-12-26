//
// Created by KiiroiSenko on 12/26/2023.
//

#pragma once
#include <queue>
#include <SDL.h>
#include <glad/glad.h>

enum class Buffer_Options
{
    None = 0,
};


class IERenderer final
{
    // Singleton renderer instance
    inline static IERenderer* RendererInstance = nullptr;

    // Game window
    SDL_Window* Window = nullptr;

    // OpenGL context
    SDL_GLContext GLContext = nullptr;

    // Render buffer pointer
    GLuint VertexBuffer = 0;

    IE_FORCEINLINE GLuint* GetBuffer(Buffer_Options Options)
    {
        switch (Options)
        {
            case Buffer_Options::None:
            default:
                return &VertexBuffer;
        }
    }

    IERenderer()  = default;
    ~IERenderer() = default;

public:

    /**
     * @brief Initialize the renderer instance and return a pointer to it. We don't want to renderer to be accessible everywhere so we make the constructor private and only allow one instantiation.
     * We save the pointer as an engine member variable so it can be accessed inside the engine class.
     * @return Pointer to the renderer singleton instance
     */
    static IERenderer* initialize();

    /**
     * @brief Poll the next frame's inputs and save them to the given queue. Also resizes the graphics context to the window size.
     * @param OutEvents Queue to save the events to
     */
    void PollFrameInputs(std::queue<SDL_Event>& OutEvents);

    /**
     * @brief Render the next frame and display it using the given data. TODO: add parameters
     */
    void RenderFrame();

    /**
     * @brief Destroy the renderer instance
     */
    void Destroy();

    /**
     * @brief Compile the shaders used by the renderer
     */
    static void CompileShaders();

    static void ResizeRendererToWindow(int Width, int Height);

    static void SaveCompiledShader() {};
};
