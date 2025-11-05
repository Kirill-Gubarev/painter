#include "render.h"

#include "term.h"
#include "render/obj/cell.h"
#include "render/obj/pixel.h"
#include "render/obj/update_state.h"

#include <cstddef>
#include <vector>

namespace render{
    using namespace detail;
    namespace detail{
        static Point screen_size; // terminal size
        static std::vector<Cell> cell_buf; // cell buffer
        // Pixel buffer.
        // Pixel_buf is 2 times bigger because it uses semi-block symbols
        // {L' ', L'▀', L'▄', L'█'}
        static std::vector<Pixel> pixel_buf;

        static RGB default_fg(255, 255, 255); // default foreground color
        static RGB default_bg(0, 0, 0); // default background color
        static RGB brush_fg = default_fg; // current terminal foreground color
        static RGB brush_bg = default_bg; // current terminal background color

        static int count_updates = 0;
    }
}

void render::detail::set_brush_fg(const RGB& color){
    if(brush_fg == color)
        return;
    brush_fg = color;
    term::set_fg_color(color);
}

void render::detail::set_brush_bg(const RGB& color){
    if(brush_bg == color)
        return;
    brush_bg = color;
    term::set_bg_color(color);
}

void render::detail::resize(Point new_size){
    screen_size = new_size;

    cell_buf.resize(screen_size.area());
    pixel_buf.resize(screen_size.area() * 2);
}

render::detail::Cell& render::detail::get_cell(const Point& p){
    return cell_buf[p.x + p.y * screen_size.x];
}

void render::init(){
    term::set_locale();
    term::set_alt_buf(true);
    term::set_cursor_visible(false);
    term::set_echo_mode(false);
    term::set_canonical_mode(false);

    term::set_fg_color(default_fg);
    term::set_bg_color(default_bg);

    screen_size = render::get_screen_size();
    resize(screen_size);
    clear_screen();
}

void render::terminate(){
    term::reset_color();
    term::set_canonical_mode(true);
    term::set_echo_mode(true);
    term::set_cursor_visible(true);
    term::set_alt_buf(false);

    cell_buf = {};
    pixel_buf = {};
}

void render::update() {
    core::Point new_size = term::get_size();
    if(new_size != screen_size)
        resize(new_size);

    // 1) pixels updating
    for(Point p(0, 0); p.y < screen_size.y; p.y++){
        for(p.x = 0; p.x < screen_size.x; p.x++){
            Cell& cell = get_cell(p);
            if(cell.update == Update_state::Update)
                continue;

            Pixel& pix1 = pixel_buf[p.x + p.y * 2 * screen_size.x];
            Pixel& pix2 = pixel_buf[p.x + (p.y * 2 + 1) * screen_size.x];

            if(pix1.update == Update_state::Update){
                if(pix2.update == Update_state::Update){
                    if(pix1.color == pix2.color)
                        set_cell(p, L'█', pix1.color, default_bg);
                    else
                        set_cell(p, L'▀', pix1.color, pix2.color);
                }
                else{
                    set_cell(p, L'▀', pix1.color, default_bg);
                }
            }
            else if(pix2.update == Update_state::Update){
                set_cell(p, L'▄', pix2.color, default_bg);
            }
            else{
                set_cell(p, L' ', default_bg);
            }
            pix1.update = Update_state::None;
            pix2.update = Update_state::None;
        }
    }

    count_updates = 0;
    // 2) cells updating
    for(Point p(0, 0); p.y < screen_size.y; p.y++){
        for(p.x = 0; p.x < screen_size.x; p.x++){
            Cell& cell = get_cell(p);
            if(cell.update == Update_state::Update){
                set_brush_fg(cell.fg);
                set_brush_bg(cell.bg);
                term::set_position(p);
                term::write(cell.glyph);
                cell.update = Update_state::Clear;
                count_updates++;
            }
            else if(cell.update == Update_state::Clear){
                clear_screen_cell(p);
                cell.update = Update_state::None;
                continue;
            }
        }
    }
}

core::Point render::get_screen_size(){
    return term::get_size();
}
core::Point render::get_canvas_size(){
    Point p = term::get_size();
    return Point(p.x, p.y * 2);
}

void render::clear_screen(const RGB& color){
    set_brush_bg(color);
    term::clear();
}

void render::clear_screen_cell(const Point& p, const RGB& color){
    set_brush_bg(color);
    term::set_position(p.x, p.y);
    term::write(L' ');
}

const core::RGB& render::get_default_fg(){
    return default_fg;
}

const core::RGB& render::get_default_bg(){
    return default_bg;
}
int render::get_count_updates(){
    return count_updates;
}

void render::set_default_fg(const RGB& color){
    default_fg = color;
}

void render::set_default_bg(const RGB& color){
    default_bg = color;
}

void render::set_cell(const Point& p, wchar_t glyph,
        const RGB& fg, const RGB& bg)
{
    if(p.x < 0 || p.x >= screen_size.x || p.y < 0 || p.y >= screen_size.y)
        return;
    cell_buf[p.x + p.y * screen_size.x] = Cell(glyph, fg, bg, Update_state::Update);
}

void render::set_pixel(const Point& p, const RGB& color) {
    if(p.x < 0 || p.x >= screen_size.x || p.y < 0 || p.y >= screen_size.y * 2)
        return;
    pixel_buf[p.x + p.y * screen_size.x] = Pixel(color, Update_state::Update);
}

void render::set_text(const Point& p, const std::string& text,
        const RGB& fg, const RGB& bg)
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
        cell_buf[start + i] = Cell(text[i], fg, bg, Update_state::Update);
}
