#include "render/render.h"
#include "core/tps_controller.h"

#include <csignal>
#include <unistd.h>
#include <cstdlib>

void signal_handler(int signal) {
    render::terminate();
    exit(1);
}

core::tps_controller fps_ctr(60.0);

int main(){
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    render::init();

    core::Point pos(0, 0);
    core::Point rect_size(10, 10);
    int step = 1;
    core::Point direction(1, 1);

    for(;;){
        fps_ctr.start_frame();

        core::Point screen_size = render::get_size();
        core::Point screen_size_pix(screen_size.x, screen_size.y * 2);

        for(int x = pos.x; x <= pos.x + rect_size.x; x++)
            render::set_pixel(core::Point(x, pos.y + rect_size.y), true, core::RGB(0, 0, 255));
        for(int y = pos.y; y <= pos.y + rect_size.y; y++)
            render::set_pixel(core::Point(pos.x + rect_size.x, y), true, core::RGB(0, 255, 0));
        for(int x = pos.x; x <= pos.x + rect_size.x; x++)
            render::set_pixel(core::Point(x, pos.y), true, core::RGB(255, 255, 0));
        for(int y = pos.y; y <= pos.y + rect_size.y; y++)
            render::set_pixel(core::Point(pos.x, y), true, core::RGB(255, 0, 0));

        if(pos.y + rect_size.y >= screen_size_pix.y - 1)
            direction = core::Point(direction.x, -1);
        if(pos.x + rect_size.x >= screen_size_pix.x - 1)
            direction = core::Point(-1, direction.y);
        if(pos.y <= 0)
            direction = core::Point(direction.x, 1);
        if(pos.x <= 0)
            direction = core::Point(1, direction.y);

        render::set_text(core::Point(0, screen_size.y - 4),
                "position: " + to_string(pos), core::RGB(255, 0, 0));
        render::set_text(core::Point(0, screen_size.y - 3),
                "direction: " + to_string(direction), core::RGB(255, 0, 0));
        render::set_text(core::Point(0, screen_size.y - 2),
                "FPS: " + std::to_string(fps_ctr.get_current_tps()), core::RGB(255, 0, 0));
        render::set_text(core::Point(0, screen_size.y - 1),
                "screen size: " + to_string(screen_size), core::RGB(255, 0, 0));

        pos += direction;
        render::update();

        fps_ctr.end_frame();
    }
    render::terminate();

    return 0;
}
