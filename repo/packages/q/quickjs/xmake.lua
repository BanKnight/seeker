package("quickjs")
    set_homepage("https://bellard.org/quickjs/")
    set_description("QuickJS is a small and embeddable Javascript engine")

    add_urls("https://github.com/c-smile/quickjspp.git")
    add_versions("2021.03.27", "2902f49b4b1cce901328802248c931622f474aba")

    add_patches("2021.03.27", path.join(os.scriptdir(), "patches", "2021.03.27", "fix.patch"), "96365C476125711BD6B7685F9D79FE99D250801681B5FD99626166C98DBC5863")

    if is_plat("linux", "macosx", "iphoneos", "cross") then
        add_syslinks("pthread", "dl", "m")
    elseif is_plat("android") then
        add_syslinks("dl", "m")
    end

    on_install("linux", "macosx", "iphoneos", "android", "windows", "cross", function (package)
        io.writefile("xmake.lua", ([[
            add_rules("mode.debug", "mode.release")
            target("quickjs")
                set_kind("static")
                add_defines("CONFIG_VERSION=\"%s\"", "_GNU_SOURCE")
                add_defines("CONFIG_BIGNUM")
                add_files("cutils.c")
                add_files("libbf.c")
                add_files("libregexp.c")
                add_files("libunicode.c")
                add_files("quickjs-libc.c")
                add_files("quickjs.c")
                add_files("libbf.c")
                add_headerfiles("quickjs-libc.h")
                add_headerfiles("quickjs.h")
                add_headerfiles("quickjs-version.h")
        ]]):format(package:version_str()))
        local configs = {}
        if package:config("shared") then
            configs.kind = "shared"
        end
        if package:is_plat("cross") then
            io.replace("quickjs.c", "#define CONFIG_PRINTF_RNDN", "")
        end

        if package:debug() then
            configs.mode = "debug"
        end
        import("package.tools.xmake").install(package, configs)
    end)

    on_test(function (package)
        assert(package:has_cfuncs("JS_NewRuntime", {includes = "quickjs.h"}))
    end)