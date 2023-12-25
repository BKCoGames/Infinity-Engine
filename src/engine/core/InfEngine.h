//
// Created by KiiroiSenko on 12/24/2023.
//

#pragma once

#include <chrono>
#include <glad/glad.h>
#include <queue>
#include <SDL.h>

class GLFWwindow;

class InfEngine
{
public:

    static bool Initialize();

    /**
     * @brief Main engine loop
     */
    void Cycle();

    IE_NODISCARD IE_FORCEINLINE static InfEngine* GetEngine() { return EngineInstance; }

protected:

    static void ProcessEvents();

private:
    // Singleton engine instance
    inline static InfEngine*  EngineInstance = nullptr;

    // Singleton renderer instance
    inline static class IERenderer* RendererInstance = nullptr;

    // TODO delete this (for test)
    inline static float TimeSinceLastPrint = 0.0f;

    // Should the window be closed on the next frame
    inline static bool bShouldCloseOnNextFrame = false;

    // Events happened during the last frame and not processed yet
    inline static std::queue<SDL_Event> LastFrameEvents = {};

    // Time of the last frame. Used for delta time calculation
    std::chrono::steady_clock::time_point lastFrameTime;

    InfEngine()  = default;
    ~InfEngine() = default;
};

// Global engine instance
#define INF_ENGINE InfEngine::GetEngine()