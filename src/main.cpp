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
    core::Point rect_size(5, 5);
    int step = 1;
    core::Point direction(1, 1);

    // main loop
    for(;;){
        fps_ctr.start_frame();

        core::Point screen_size = render::get_screen_size();
        core::Point canvas_size = render::get_canvas_size();

        core::RGB color1(255, 255, 255);
        core::RGB color2(100, 100, 100);
/*
        int chunk_size = 4;
        for(int chunk_y = 0; chunk_y < canvas_size.y; chunk_y += chunk_size){
            for(int chunk_x = 0; chunk_x < canvas_size.x; chunk_x += chunk_size){
                if((chunk_y + chunk_x) / chunk_size % 2 == 0)
                    continue;
                core::RGB color = ((chunk_x / chunk_size + chunk_y / chunk_size) % 2 == 0) ? color1 : color2;
                for(int y = chunk_y; y < chunk_y + chunk_size; y++){
                    for(int x = chunk_x; x < chunk_x + chunk_size; x++){
                        render::set_pixel(core::Point(x, y), color);
                    }
                }
            }
        }
    */

        for(int x = pos.x; x <= pos.x + rect_size.x; x++)
            render::set_pixel(core::Point(x, pos.y + rect_size.y), core::RGB(0, 0, 255));
        for(int y = pos.y; y <= pos.y + rect_size.y; y++)
            render::set_pixel(core::Point(pos.x + rect_size.x, y), core::RGB(0, 255, 0));
        for(int x = pos.x; x <= pos.x + rect_size.x; x++)
            render::set_pixel(core::Point(x, pos.y), core::RGB(255, 255, 0));
        for(int y = pos.y; y <= pos.y + rect_size.y; y++)
            render::set_pixel(core::Point(pos.x, y), core::RGB(255, 0, 0));

        if(pos.y + rect_size.y >= canvas_size.y - 1)
            direction = core::Point(direction.x, -1);
        if(pos.x + rect_size.x >= canvas_size.x - 1)
            direction = core::Point(-1, direction.y);
        if(pos.y <= 0)
            direction = core::Point(direction.x, 1);
        if(pos.x <= 0)
            direction = core::Point(1, direction.y);

        render::set_text(core::Point(0, screen_size.y - 5),
                "position: " + to_string(pos), core::RGB(255, 0, 0));
        render::set_text(core::Point(0, screen_size.y - 4),
                "direction: " + to_string(direction), core::RGB(255, 0, 0));
        render::set_text(core::Point(0, screen_size.y - 3),
                "count updates: " + std::to_string(render::get_count_updates()), core::RGB(255, 0, 0));
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
