//
// Created by Ben Gotts on 25/01/2025.
//

#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include "../graphics/Renderer.h"
#include "../core/Scene.h"
#include "../debug/DebugProfilerUI.h"
#include "Input.h"

using namespace glm;

namespace BG3DRenderer::Core {
    class Application {
    private:
        Window appWindow;
        Renderer appRenderer;

        Scene appScene;
        Input appInput;

        Debug::DebugProfilerUI profilerUI;

        float deltaTime;
        float lastFrame;
    public:
        Application();
        ~Application();
        void Run();

        static float DeltaTime;
    };
}


#endif //APPLICATION_H
