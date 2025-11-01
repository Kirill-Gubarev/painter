#include "render/render.h"
#include <csignal>
#include <unistd.h>

#include <cstdlib>
#include <chrono>
#include <thread>

void signal_handler(int signal) {
    render::terminate();
    exit(1);
}

int main(){
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    render::init();

    Point pos(0, 0);
    Point rect_size(10, 10);
    int step = 1;
    Point direction(1, 1);

    for(;;){
        Point screen_size = render::get_size();
        Point screen_size_pix(screen_size.x, screen_size.y * 2);

        for(int x = pos.x; x <= pos.x + rect_size.x; x++)
            render::set_pixel(Point(x, pos.y + rect_size.y), true, RGB(0, 0, 255));
        for(int y = pos.y; y <= pos.y + rect_size.y; y++)
            render::set_pixel(Point(pos.x + rect_size.x, y), true, RGB(0, 255, 0));
        for(int x = pos.x; x <= pos.x + rect_size.x; x++)
            render::set_pixel(Point(x, pos.y), true, RGB(255, 255, 0));
        for(int y = pos.y; y <= pos.y + rect_size.y; y++)
            render::set_pixel(Point(pos.x, y), true, RGB(255, 0, 0));

        if(pos.y + rect_size.y >= screen_size_pix.y - 1)
            direction = Point(direction.x, -1);
        if(pos.x + rect_size.x >= screen_size_pix.x - 1)
            direction = Point(-1, direction.y);
        if(pos.y <= 0)
            direction = Point(direction.x, 1);
        if(pos.x <= 0)
            direction = Point(1, direction.y);

        render::set_text(Point(0, screen_size.y - 2), "position: " + to_string(pos), RGB(255, 0, 0));
        render::set_text(Point(0, screen_size.y - 1), "direction: " + to_string(direction), RGB(255, 0, 0));

        pos += direction;
        render::update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    render::terminate();

    return 0;
}
