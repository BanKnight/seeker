add_repositories("repo repo")

add_rules("mode.debug", "mode.release")

add_requires("glfw","tidy","pugixml")
add_requires("quickjs",{debug = true})
add_requires("libuv",{debug = true})
add_requires("glad",{debug = true})
add_requires("spdlog",{debug = true})
add_requires("skia",{debug = true,configs = {pdf = false,nvpr = false}})

target("seeker")
    set_kind("binary")
    add_files("src/**.cpp|test.cpp")
    add_defines("NOMINMAX")
    add_defines("_HAS_DEPRECATED_RESULT_OF")
    add_cxxflags("/Wv:18")
    add_includedirs("include")
    add_includedirs("src")
    set_languages("c++latest")
    add_packages("glad", "glfw","quickjs","tidy","pugixml","libuv","spdlog","skia")

target("test")
    set_kind("binary")
    add_files("src/test.cpp")
    add_defines("NOMINMAX")
    add_defines("_HAS_DEPRECATED_RESULT_OF")
    set_languages("c++latest")
    add_packages("libuv")
    add_packages("glad", "glfw","quickjs","tidy","pugixml","libuv","spdlog","skia")

--     add_packages("glad", "glfw","tidy","pugixml")


