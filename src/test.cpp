#include <iostream>
#include <algorithm>
#include <limits>
#include <stdint.h>
#include <type_traits>
#include <uv.h>

#include "quickjs-libc.h"
#include <core/SkCanvas.h>


int main(int argc, char **argv)
{
    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContextRaw(rt);

    if(ctx != nullptr)
    {
        std::cout << "ok" << std::endl;
    }

    // SkPaint paint;
	// 	paint.setColor(SK_ColorWHITE);

    uv_run(uv_default_loop(), UV_RUN_DEFAULT);

    return 0;
}
