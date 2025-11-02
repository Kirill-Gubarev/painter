#include "render.h"

#include "term.h"
#include "render/cell.h"
#include "render/pixel.h"

#include <cstddef>

namespace render{
    using namespace detail;
    namespace detail{
        static core::Point screen_size; // terminal size
        static Cell* cell_buf = nullptr; // cell buffer
        // pixel_buf is 2 times bigger because it uses semi-block symbols
        // {L' ',L'▀',L'▄',L'█'}
        static Pixel* pixel_buf = nullptr; // pixel buffer

        static core::RGB global_fg(255, 255, 255); // global foreground color
        static core::RGB global_bg(0, 0, 0); // global background color
        static core::RGB brush_fg = global_fg; // current terminal foreground color
        static core::RGB brush_bg = global_bg; // current terminal background color
    }
}

void render::detail::set_brush_fg(const core::RGB& color){
    if(brush_fg == color)
        return;
    brush_fg = color;
    term::set_fg_color(color);
}

void render::detail::set_brush_bg(const core::RGB& color){
    if(brush_bg == color)
        return;
    brush_bg = color;
    term::set_bg_color(color);
}

void render::detail::resize(core::Point new_size){
    screen_size = new_size;

    if(cell_buf)
        delete[] cell_buf;
    if(pixel_buf)
        delete[] pixel_buf;

    cell_buf = new Cell[screen_size.area()];
    pixel_buf = new Pixel[screen_size.area() * 2];
}

render::detail::Cell& render::detail::get_cell(int x, int y){
    return cell_buf[x + y * screen_size.x];
}

void render::init(){
    term::set_locale();
    term::set_alt_buf(true);
    term::set_cursor_visible(false);
    term::set_echo_mode(false);
    term::set_canonical_mode(false);

    screen_size = term::get_size();
    resize(screen_size);
    clear_screen();
}

void render::terminate(){
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
    core::Point new_size = term::get_size();
    if(new_size != screen_size)
        resize(new_size);

    // 1) pixels updating
    for(size_t y = 0; y < screen_size.y; y++){
        for(size_t x = 0; x < screen_size.x; x++){
            Cell& cell = get_cell(x, y);
            if(cell.updates_left == 2)
                continue;

            Pixel& pix1 = pixel_buf[x + y * 2 * screen_size.x];
            Pixel& pix2 = pixel_buf[x + (y * 2 + 1) * screen_size.x];

            if(pix1.changed && pix1.filled){
                if(pix2.changed && pix2.filled){
                    if(pix1.color == pix2.color)
                        set_cell(core::Point(x, y), L'█', pix1.color, global_bg);
                    else
                        set_cell(core::Point(x, y), L'▀', pix1.color, pix2.color);
                }
                else{
                    set_cell(core::Point(x, y), L'▀', pix1.color, global_bg);
                }
            }
            else if(pix2.changed && pix2.filled){
                set_cell(core::Point(x, y), L'▄', pix2.color, global_bg);
            }
            else{
                set_cell(core::Point(x, y), L' ', global_bg);
            }
            pix1.changed = false;
            pix2.changed = false;
        }
    }

    // 2) cells updating
    for(size_t y = 0; y < screen_size.y; y++){
        for(size_t x = 0; x < screen_size.x; x++){
            Cell& cell = get_cell(x, y);
            if(cell.updates_left == 0)
                continue;

            // clear the previous painted cells
            if(cell.updates_left == 1){
                clear_screen_cell(x, y);
                cell.updates_left--; // 1 -> 0
                continue;
            }

            // write the cell
            set_brush_fg(cell.fg);
            set_brush_bg(cell.bg);
            term::set_position(x, y);
            term::write(cell.glyph);
            cell.updates_left--; // 2 -> 1
        }
    }
}

core::Point render::get_size(){
    return term::get_size();
}

void render::clear_screen(){
    // preparation terminal settings
    term::set_fg_color(global_fg);
    term::set_bg_color(global_bg);
    term::return_cursor();

    // clearing screen
    term::clear();

    // reset terminal settings
    term::set_fg_color(brush_fg);
    term::set_bg_color(brush_bg);
}

void render::clear_screen_cell(int x, int y){
    set_brush_bg(global_bg);
    term::set_position(x, y);
    term::write(L' ');
}

const core::RGB& render::get_global_fg(){
    return global_fg;
}

const core::RGB& render::get_global_bg(){
    return global_bg;
}

void render::set_global_fg(const core::RGB& color){
    global_fg = color;
}

void render::set_global_bg(const core::RGB& color){
    global_bg = color;
}

void render::set_cell(const core::Point& p, wchar_t glyph,
        const core::RGB& fg, const core::RGB& bg)
{
    if(p.x < 0 || p.x >= screen_size.x || p.y < 0 || p.y >= screen_size.y)
        return;
    // 2 is the count of pending cell updates
    cell_buf[p.x + p.y * screen_size.x] = Cell(glyph, fg, bg, 2);
}

void render::set_pixel(const core::Point& p, bool filled, const core::RGB& color) {
    if(p.x < 0 || p.x >= screen_size.x || p.y < 0 || p.y >= screen_size.y * 2)
        return;
    pixel_buf[p.x + p.y * screen_size.x] = Pixel(filled, color, true);
}

void render::set_text(const core::Point& p, const std::string& text,
        const core::RGB& fg, const core::RGB& bg)
{
    size_t buf_length = screen_size.area();
    size_t text_length = text.length();

    size_t start = p.x + p.y * screen_size.x;
    if(start >= buf_length)
        return;

    size_t end = start + text_length;
    if(end > buf_length)
        text_length -= end - buf_length;

    for(size_t i = 0; i < text_length; i++)
        cell_buf[start + i] = Cell(text[i], fg, bg, 2);
}
