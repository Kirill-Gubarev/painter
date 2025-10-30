#include "term.h"
#include "render/render.h"
#include <csignal>
#include <unistd.h>

void signal_handler(int signal) {
    render::cleanup();
    exit(1);
}

int main(){
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    render::setup();

    Point start(10, 10);
    Point end(20, 20);
    int step = 1;

    for(char ch; (ch = term::get_char());){
        if(ch == 'q')
            break;
        for(int x = start.x; x <= end.x; x++)
            render::set_pixel(Point(x, end.y), true, RGB(0, 0, 255));
        for(int y = start.y; y <= end.y; y++)
            render::set_pixel(Point(end.x, y), true, RGB(0, 255, 0));
        for(int x = start.x; x <= end.x; x++)
            render::set_pixel(Point(x, start.y), true, RGB(255, 255, 0));
        for(int y = start.y; y <= end.y; y++)
            render::set_pixel(Point(start.x, y), true, RGB(255, 0, 0));
        render::update();
        start.x += step;
        start.y += step;
        end.x += step;
        end.y += step;
    }
    render::cleanup();

    return 0;
}
