#include <stdio.h>

#include "core.h"
#include "common.h"

#include "config.h"

void on_idle(uv_idle_t* handle) {

    glfwPollEvents();

    // printf("Idling...\n");
}

void seeker::init()
{
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW!\n");
        return;
    }

    init_config();

    printf("init ok\n");
}

void seeker::loop()
{
    uv_idle_t idler;

    uv_idle_init(uv_default_loop(), &idler);
    uv_idle_start(&idler, on_idle);

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    uv_loop_close(uv_default_loop());
}

void seeker::uninit()
{
    uv_loop_close(uv_default_loop());
}
