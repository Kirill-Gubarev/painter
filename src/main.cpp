#include "render/render.h"
#include "core/tps_controller.h"

#include <csignal>
#include <unistd.h>
#include <cstdlib>

using core::Point;
using core::RGB;

void signal_handler(int signal) {
    render::terminate();
    exit(1);
}

core::tps_controller fps_ctr(60.0);

void draw_checkerboard(const Point& canvas_size, int chunk_size){
    const RGB color(50);

    for(int chunk_y = 0; chunk_y < canvas_size.y; chunk_y += chunk_size){
        for(int chunk_x = 0; chunk_x < canvas_size.x; chunk_x += chunk_size){
            if((chunk_y + chunk_x) / chunk_size % 2 == 0)
                continue;
            for(int y = chunk_y; y < chunk_y + chunk_size; y++){
                for(int x = chunk_x; x < chunk_x + chunk_size; x++){
                    render::set_pixel(Point(x, y), color);
                }
            }
        }
    }
}
void draw_square(const Point& pos, const Point& size, const RGB& color){
    for(int x = pos.x; x <= pos.x + size.x; x++)
        render::set_pixel(Point(x, pos.y + size.y), color);
    for(int y = pos.y; y <= pos.y + size.y; y++)
        render::set_pixel(Point(pos.x + size.x, y), color);
    for(int x = pos.x; x <= pos.x + size.x; x++)
        render::set_pixel(Point(x, pos.y), color);
    for(int y = pos.y; y <= pos.y + size.y; y++)
        render::set_pixel(Point(pos.x, y), color);
}

int main(){
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    render::init();

    const size_t poses_size = 10;
    Point poses[poses_size]{};
    Point rect_size(10, 10);
    Point direction(1, 1);

    // main loop
    for(;;){
        fps_ctr.start_frame();
        Point screen_size = render::get_screen_size();
        Point canvas_size = render::get_canvas_size();

        draw_checkerboard(canvas_size, 10);

        // square drawing
        for(int i = poses_size - 1; i >= 0; i--)
            draw_square(poses[i], rect_size, RGB(0, 0, static_cast<uint8_t>(255.0f - 255.0f / poses_size * i)));
        if(poses[0].y + rect_size.y >= canvas_size.y - 1)
            direction = Point(direction.x, -1);
        if(poses[0].x + rect_size.x >= canvas_size.x - 1)
            direction = Point(-1, direction.y);
        if(poses[0].y <= 0)
            direction = Point(direction.x, 1);
        if(poses[0].x <= 0)
            direction = Point(1, direction.y);

        for(int i = poses_size - 1; i >= 1; i--)
            poses[i] = poses[i - 1];
        poses[0] += direction;

        // stats printing
        render::Stats stats = render::get_stats();
        render::set_text(Point(0, screen_size.y - 6),
                "rect position: " + to_string(poses[0]), RGB(255, 0, 0));
        render::set_text(Point(0, screen_size.y - 5),
                "direction: " + to_string(direction), RGB(255, 0, 0));
        render::set_text(Point(0, screen_size.y - 4),
                "update count: " + std::to_string(stats.update_count), RGB(255, 0, 0));
        render::set_text(Point(0, screen_size.y - 3),
                "clear count: " + std::to_string(stats.clear_count), RGB(255, 0, 0));
        render::set_text(Point(0, screen_size.y - 2),
                "FPS: " + std::to_string(fps_ctr.get_current_tps()), RGB(255, 0, 0));
        render::set_text(Point(0, screen_size.y - 1),
                "screen size: " + to_string(screen_size), RGB(255, 0, 0));

        render::update();
        fps_ctr.end_frame();
    }
    render::terminate();

    return 0;
}
