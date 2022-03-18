#include "core.h"
#include "core/SkPaint.h"

int main(int argc, char **argv)
{
    seeker::init();

    auto id = seeker::new_window("index.js 123");      

    seeker::start_window(id);

    seeker::loop();

    seeker::uninit();

    return 0;
}