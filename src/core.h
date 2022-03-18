#pragma once

#include <string>

namespace seeker
{
    void init();

    void loop();

    void uninit();

    int new_window(const std::string & args);

    void start_window(int id);

    void stop_window(int id);
}
