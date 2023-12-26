//
// Created by KiiroiSenko on 12/24/2023.
//

#include "InfEngine.h"
#include "CoreIncludes.h"
#include <SDL.h>
#include <iostream>
#include <renderer/IERenderer.h>


bool InfEngine::Initialize()
{
    IE_ASSERT_MSG(EngineInstance == nullptr, "Multiple InfEngine::Initialize() calls detected! Engine is already initialized!"); // Does not trigger in release build
    if (EngineInstance != nullptr)
    {
        return false;
    }
    std::cout << "Initializing engine" << std::endl;

    // Engine object initialization
    EngineInstance                = new InfEngine();
    EngineInstance->lastFrameTime = std::chrono::steady_clock::now();

    std::cout << "Hello, World!" << std::endl;


    if (RendererInstance = IERenderer::initialize(); RendererInstance == nullptr)
    {
        std::cout << "Renderer initialization failed!" << std::endl;
        return false;
    }

    return true;
}

void InfEngine::Cycle()
{
    while(!bShouldCloseOnNextFrame)
    {
        // Delta time calculation
        auto now= std::chrono::steady_clock::now();
        std::chrono::duration<float> Diff = now - lastFrameTime;
        float deltaTime = Diff.count();
        lastFrameTime   = now;


        TimeSinceLastPrint += deltaTime;
        if (TimeSinceLastPrint > 1.0f)
        {
            std::cout << "FPS: " << ceil(1/deltaTime) << std::endl;
            TimeSinceLastPrint -= 1.0f;
        }

        RendererInstance->PollFrameInputs(LastFrameEvents);
        ProcessEvents();

        // TODO: Engine core logic here (e.g. game logic, physics, etc.)


        // Check and call events and swap the buffers
        RendererInstance->RenderFrame();
    }

    RendererInstance->Destroy();
}

void InfEngine::ProcessEvents()
{
    while(!LastFrameEvents.empty())
    {
        SDL_Event Event = LastFrameEvents.front();
        LastFrameEvents.pop();

        switch (Event.type)
        {
            case SDL_QUIT:
                bShouldCloseOnNextFrame = true;
                break;
            case SDL_WINDOWEVENT:
                if (Event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    IERenderer::ResizeRendererToWindow(Event.window.data1, Event.window.data2);
                }
                break;
            case SDL_KEYDOWN:
                if (Event.key.keysym.sym == SDLK_ESCAPE)
                {
                    bShouldCloseOnNextFrame = true;
                }
                break;
            default:
                break;
        }
    }
}
