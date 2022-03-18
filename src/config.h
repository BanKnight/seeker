#pragma once

#include <string>
#include <filesystem>

namespace seeker
{
    struct Config
    {
        // std::filesystem::path search; //搜索路径
        std::string bootstrap;
    };

    bool init_config();

    const Config &get_config();

    std::string get_boostrap();
}