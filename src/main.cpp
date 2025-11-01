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

    Point start(0, 0);
    Point rect_size(10, 10);
    int step = 1;
    Point direction(1, 1);

    for(;;){
        Point screen_size = render::get_size();
        screen_size.y *= 2;
        for(int x = start.x; x <= start.x + rect_size.x; x++)
            render::set_pixel(Point(x, start.y + rect_size.y), true, RGB(0, 0, 255));
        for(int y = start.y; y <= start.y + rect_size.y; y++)
            render::set_pixel(Point(start.x + rect_size.x, y), true, RGB(0, 255, 0));
        for(int x = start.x; x <= start.x + rect_size.x; x++)
            render::set_pixel(Point(x, start.y), true, RGB(255, 255, 0));
        for(int y = start.y; y <= start.y + rect_size.y; y++)
            render::set_pixel(Point(start.x, y), true, RGB(255, 0, 0));

        if(start.y + rect_size.y >= screen_size.y - 1)
            direction = Point(direction.x, -1);
        if(start.x + rect_size.x >= screen_size.x - 1)
            direction = Point(-1, direction.y);
        if(start.y <= 0)
            direction = Point(direction.x, 1);
        if(start.x <= 0)
            direction = Point(1, direction.y);

        render::update();
        start = start + direction;
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    render::terminate();

    return 0;
}
