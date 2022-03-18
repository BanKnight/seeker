
#include "config.h"

static seeker::Config config;

bool seeker::init_config()
{

    // config.search = std::filesystem::canonical("D:/workspace/seeker/scripts");
    config.bootstrap = "D:/workspace/seeker/scripts/bootstrap.js";

    return true;
}

const seeker::Config & seeker::get_config()
{
    return config;
}

std::string seeker::get_boostrap()
{
    return config.bootstrap;
}


