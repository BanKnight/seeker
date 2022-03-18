#pragma once

#include <string>

#include <GLFW/glfw3.h>
#include <uv.h>
#define SK_GL // Doesn't work without this
#include <gpu/GrBackendSurface.h>
#include <gpu/GrDirectContext.h>
#include <gpu/gl/GrGLInterface.h>
#include <core/SkCanvas.h>
#include <core/SkColorSpace.h>
#include <core/SkSurface.h>

#include "js-runtime/runtime.h"

namespace seeker
{
    struct Window
    {
        int32_t id;
        int32_t width;
        int32_t height;
        std::string title;
        std::string args;
        uv_loop_t *loop = nullptr;
        GLFWwindow *real = nullptr;
        JS *js = nullptr;
        GrDirectContext *sContext = nullptr;
        SkSurface *sSurface = nullptr;
    };

}