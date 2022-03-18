#include "js-modules/Canvas2d.h"
#include <core/SkCanvas.h>
#include <core/SkColorSpace.h>
#include <core/SkPath.h>
#include <core/SKPaint.h>

#include <core/SkBitmap.h>

struct CanvasContext
{
    SkCanvas *canvas = nullptr;
    SkBitmap *bitmap = nullptr;
    SkPaint fill;
    SkPaint stroke;
    // 绘制图形时使用的Path对象
    SkPath path;
};

#define countof(x) (sizeof(x) / sizeof((x)[0]))

static JSClassID js_class_id;

static JSValue js_create_canvas2d(JSContext *ctx, JSValueConst this_val,
                                  int argc, JSValueConst *argv)
{
    // 返回jscanvas对象
    return JS_NewObjectClass(ctx, js_class_id);
}

static JSValue js_new_class(JSContext *ctx,
                            JSValueConst new_target,
                            int argc, JSValueConst *argv)
{

    // 创建C的context对象
    CanvasContext *context = new CanvasContext;
    SkBitmap *bmp = new SkBitmap;
    // 这里需要创建Skia绘制时的图像buffer，需要对接到设备屏幕
    // bmp->setConfig(SkBitmap::kARGB_8888_Config, screenWidth, screenHeight);
    // bmp->setPixels(fb_buf);
    // TODO 这边示例先用内存buffer代替下，创建一块200x200的buffer

    auto image = SkImageInfo::Make(200, 200, SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kPremul_SkAlphaType);

    bmp->allocPixelsFlags(image, 0);

    context->bitmap = bmp;
    context->canvas = new SkCanvas(*bmp);
    context->stroke.setStyle(SkPaint::kStroke_Style);

    JSValue proto = JS_GetPropertyStr(ctx, new_target, "prototype");

    /* using new_target to get the prototype is necessary when the
       class is extended. */
    proto = JS_GetPropertyStr(ctx, new_target, "prototype");
    if (JS_IsException(proto))
        return JS_EXCEPTION;

    JSValue obj = JS_NewObjectProtoClass(ctx, proto, js_class_id);

    JS_FreeValue(ctx, proto);

    if (JS_IsException(obj))
    {
        return JS_EXCEPTION;
    }

    JS_SetOpaque(obj, context);
    return obj;
}

static void js_del_class(JSRuntime *rt, JSValue val)
{
    CanvasContext *context = (CanvasContext *)JS_GetOpaque(val, js_class_id);
    if (context)
    {
        delete context->bitmap;
        delete context->canvas;
        delete context;
    }
};

static JSClassDef js_point_class = {
    "Canvas2d",
    js_del_class,
};


static JSValue js_get_fillstyle(JSContext *ctx, JSValueConst this_val, int magic)
{
    return JS_EXCEPTION;
}


static JSValue js_set_fillstyle(JSContext *ctx, JSValueConst this_val, JSValue val, int magic)
{
    auto context = (CanvasContext *)JS_GetOpaque2(ctx, this_val, js_class_id);

    if (context == NULL)
        return JS_EXCEPTION;

    if (JS_IsString(val))
    {
        const char *jcolor = JS_ToCString(ctx, val);
        // 通过字符串解析为RGBA色值
        // 颜色格式可能是#RGB, #RRGGBB, rgb(r,g,b), rgba(r,g,b,a)以及HSL等等
        // 这里先不实现，先简单直接写死红色先吧
        // 给fillPaint设置颜色
        context->fill.setColor(SkColorSetARGB(0xFF, 0xFF, 0x0, 0x0));
        JS_FreeCString(ctx, jcolor);
    }
    else if (JS_IsObject(val))
    {
        // 看W3C标准规范，fillStyle可能是CanvasGradient，包括线性渐变和径向渐变，这里先不实现
    }

            return JS_EXCEPTION;

}

static const JSCFunctionListEntry js_proto_funcs[] = {
    JS_CGETSET_MAGIC_DEF("fillStyle", js_get_fillstyle, js_set_fillstyle, 0),
};

static int js_init(JSContext *ctx, JSModuleDef *m)
{

    {
        auto value = JS_NewCFunction(ctx, js_create_canvas2d, "createCanvas2d", 1);

        JS_SetModuleExport(ctx, m, "createCanvas2d", value);
    }

    {
        JSValue js_proto, js_class;

        /* create the Point class */
        JS_NewClassID(&js_class_id);
        JS_NewClass(JS_GetRuntime(ctx), js_class_id, &js_point_class);

        js_proto = JS_NewObject(ctx);
        JS_SetPropertyFunctionList(ctx, js_proto, js_proto_funcs, countof(js_proto_funcs));

        js_class = JS_NewCFunction2(ctx, js_new_class, "WebGL2RenderingContext", 2, JS_CFUNC_constructor, 0);
        /* set proto.constructor and ctor.prototype */
        JS_SetConstructor(ctx, js_class, js_proto);
        JS_SetClassProto(ctx, js_class_id, js_proto);

        JS_SetModuleExport(ctx, m, "WebGL2RenderingContext", js_class);
    }

    return 0;
}

JSModuleDef *js_init_module_canvas2d(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_init);
    if (!m)
        return NULL;
    JS_AddModuleExport(ctx, m, "createCanvas2d");
    return m;
}