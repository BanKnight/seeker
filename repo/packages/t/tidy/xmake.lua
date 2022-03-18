package("tidy")
    set_homepage("https://www.html-tidy.org")
    set_description("The granddaddy of HTML tools, with support for modern standards")

    add_urls("https://github.com/htacg/tidy-html5.git")
    add_versions("5.9.17", "14223a95a8ee1f0b0d8fa46a5f13fd38aea8b903")

    on_install("windows", "linux", "macosx","mingw", function (package)
        local configs = {}
        import("package.tools.cmake").install(package, configs)
    end)
    on_test(function (package)
        assert(package:has_cfuncs("tidyCreate", {includes = "tidy.h"}))
    end)