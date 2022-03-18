#include <vector>
#include "js-runtime/runtime.h"
#include "config.h"

namespace seeker
{

    // JSModuleDef *js_module_loader(JSContext *ctx,
    //                               const char *module_name, void *opaque)
    // {
    //     JSModuleDef *m;

    //     if (has_suffix(module_name, ".so"))
    //     {
    //         m = js_module_loader_so(ctx, module_name);
    //     }
    //     else
    //     {
    //         size_t buf_len;
    //         uint8_t *buf;
    //         JSValue func_val;

    //         buf = js_load_file(ctx, &buf_len, module_name);
    //         if (!buf)
    //         {
    //             JS_ThrowReferenceError(ctx, "could not load module filename '%s'",
    //                                    module_name);
    //             return NULL;
    //         }

    //         /* compile the module */
    //         func_val = JS_Eval(ctx, (char *)buf, buf_len, module_name,
    //                            JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
    //         js_free(ctx, buf);
    //         if (JS_IsException(func_val))
    //             return NULL;
    //         /* XXX: could propagate the exception */
    //         js_module_set_import_meta(ctx, func_val, TRUE, FALSE);
    //         /* the module is already referenced, so we must free it */
    //         m = JS_VALUE_GET_PTR(func_val);
    //         JS_FreeValue(ctx, func_val);
    //     }
    //     return m;
    // }

    JS *new_runtime()
    {
        JSRuntime *rt;
        JSContext *ctx;
        rt = JS_NewRuntime();
        ctx = JS_NewContextRaw(rt);
        JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
        JS_AddIntrinsicBaseObjects(ctx);
        JS_AddIntrinsicDate(ctx);
        JS_AddIntrinsicEval(ctx);
        JS_AddIntrinsicStringNormalize(ctx);
        JS_AddIntrinsicRegExp(ctx);
        JS_AddIntrinsicJSON(ctx);
        JS_AddIntrinsicProxy(ctx);
        JS_AddIntrinsicMapSet(ctx);
        JS_AddIntrinsicTypedArrays(ctx);
        JS_AddIntrinsicPromise(ctx);
        JS_AddIntrinsicBigInt(ctx);

        auto runtime = new JS();

        runtime->rt = rt;
        runtime->ctx = ctx;

        // js_std_add_helpers(ctx, argc, argv);

        return runtime;
    }

    void enter_runtime(JS *runtime, const std::string &args)
    {
        std::vector<std::string> arg_array;

        auto last = 0;
        auto count = 0;

        for (auto i = 0; i < args.length(); ++i)
        {
            auto c = args[i];
            if (c != ' ')
            {
                count++;
                continue;
            };

            if (count > 0)
            {
                arg_array.push_back(args.substr(last, count));
                count = 0;
            };

            last = i + 1;
        };

        if (count > 0)
        {
            arg_array.push_back(args.substr(last, count));
        };

        int argc = arg_array.size();
        char **argv = new char *[argc];

        for (auto i = 0; i < argc; ++i)
        {
            argv[i] = (char *)arg_array[i].c_str();
        }

        js_std_add_helpers(runtime->ctx, argc, argv);

        delete[] argv;

        auto bootstrap = get_boostrap();

        size_t buf_len;

        auto buf = js_load_file(runtime->ctx, &buf_len, bootstrap.c_str());

        JS_Eval(runtime->ctx, (const char *)buf, buf_len, bootstrap.c_str(), JS_EVAL_TYPE_MODULE);
    }
}