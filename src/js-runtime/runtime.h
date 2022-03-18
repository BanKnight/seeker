#pragma once

#include <string>
#include "quickjs-libc.h"

namespace seeker
{
    struct JS
    {
        JSRuntime *rt = nullptr;
        JSContext *ctx  = nullptr;
    };

    JS * new_runtime();

    void delete_runtime(JS* runtime);

    void import_skia(JS *runtime);

    void enter_runtime(JS* runtime,const std::string & args);
}