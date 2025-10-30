#include "render.h"

#include "term.h"
#include "render/cell.h"
#include "render/pixel.h"

namespace render{
    Point size;
    Cell* cell_buf;
    Pixel* pixel_buf;

    RGB global_fg(255, 255, 255);
    RGB global_bg(0, 0, 0);
    RGB brush_fg = global_fg;
    RGB brush_bg = global_bg;

    void set_fg_color(const RGB& color){
        if(brush_fg == color)
            return;
        brush_fg = color;
        term::set_fg_color(color);
    }
    void set_bg_color(const RGB& color){
        if(brush_bg == color)
            return;
        brush_bg = color;
        term::set_bg_color(color);
    }
    void resize(Point new_size){
        size = new_size;

        if(cell_buf)
            delete[] cell_buf;
        if(pixel_buf)
            delete[] pixel_buf;

        cell_buf = new Cell[size.area()];
        pixel_buf = new Pixel[size.area() * 2];
    }
    Cell& get_cell(int x, int y){
        return cell_buf[x + y * size.x];
    }
    void clear_screen_cell(int x, int y){
        set_bg_color(global_bg);
        term::set_position(x, y);
        term::write(L' ');
    }
}
void render::set_global_fg(const RGB& color){
    global_fg = color;
}
void render::set_global_bg(const RGB& color){
    global_bg = color;
}
void render::clear_screen(){
    term::set_fg_color(global_fg);
    term::set_bg_color(global_bg);
    term::return_cursor();
    for(size_t i = 0; i < size.area(); i++)
        term::write(L' ');
    term::set_fg_color(brush_fg);
    term::set_bg_color(brush_bg);
}

void render::set_cell(const Point& p, wchar_t glyph, const RGB& fg, const RGB& bg){
    if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y)
        return;
    cell_buf[p.x + p.y * size.x] = Cell(glyph, fg, bg, 2);
}
void render::set_pixel(const Point& p, bool filled, const RGB& color){
    if(p.x < 0 || p.x >= size.x || p.y < 0 || p.y >= size.y * 2)
        return;
    pixel_buf[p.x + p.y * size.x] = Pixel(filled, color, true);
}

void render::setup(){
    term::set_locale();
    term::set_alt_buf(true);
    term::set_cursor_visible(false);
    term::set_echo_mode(false);
    term::set_canonical_mode(false);

    size = term::get_size();
    resize(size);
    clear_screen();
}
void render::cleanup(){
    term::reset_color();
    term::set_canonical_mode(true);
    term::set_echo_mode(true);
    term::set_cursor_visible(true);
    term::set_alt_buf(false);

    if(cell_buf)
        delete[] cell_buf;
    if(pixel_buf)
        delete[] pixel_buf;
}

void render::update() {
    Point new_size = term::get_size();
    if(new_size != size)
        resize(new_size);

    for(size_t y = 0; y < size.y; y++){
        for(size_t x = 0; x < size.x; x++){
            Cell& cell = get_cell(x, y);
            if(cell.updates_left == 2)
                continue;

            Pixel& pix1 = pixel_buf[x + y * 2 * size.x];
            Pixel& pix2 = pixel_buf[x + (y * 2 + 1) * size.x];

            if(pix1.changed && pix1.filled){
                if(pix2.changed && pix2.filled){
                    if(pix1.color == pix2.color)
                        set_cell(Point(x, y), L'█', pix1.color, global_bg);
                    else
                        set_cell(Point(x, y), L'▀', pix1.color, pix2.color);
                }
                else{
                    set_cell(Point(x, y), L'▀', pix1.color, global_bg);
                }
            }
            else if(pix2.changed && pix2.filled){
                set_cell(Point(x, y), L'▄', pix2.color, global_bg);
            }
            else{
                set_cell(Point(x, y), L' ', global_bg);
            }
            pix1.changed = false;
            pix2.changed = false;
        }
    }

    for(size_t y = 0; y < size.y; y++){
        for(size_t x = 0; x < size.x; x++){
            Cell& cell = get_cell(x, y);
            if(cell.updates_left == 0)
                continue;
            if(cell.updates_left == 1){
                clear_screen_cell(x, y);
                cell.updates_left--;
                continue;
            }

            render::set_fg_color(cell.fg);
            render::set_bg_color(cell.bg);

            term::set_position(x, y);
            term::write(cell.glyph);
            cell.updates_left--;
        }
    }
}
