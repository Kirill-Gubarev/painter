#include "render.h"

#include "term.h"
#include "core/rgb.h"
#include "core/point.h"

struct Cell;

Point size;
RGB brush_fg;
RGB brush_bg;
Cell* buf;

struct Cell{
    wchar_t ch;
    RGB fg, bg;
    bool changed;

    Cell(wchar_t ch = L' ',
            RGB fg = RGB(255, 255, 255),
            RGB bg = RGB(0, 0, 0)):
        ch(ch),
        fg(fg),
        bg(bg),
        changed(true)
    {}
};
bool operator==(Cell c1, Cell c2){
    return c1.ch == c2.ch && c1.fg == c2.fg && c1.bg == c2.bg;
}
bool operator!=(Cell c1, Cell c2){
    return c1.ch != c2.ch || c1.fg != c2.fg || c1.bg != c2.bg;
}

void buf_set(const Cell& new_cell, Point p){
    Cell& curr_cell = buf[p.x + p.y * size.x];
    curr_cell = new_cell;
    curr_cell.changed = true;
}

void render::setup(){
    term::set_locale();
    term::set_alt_buf(true);
    term::set_cursor_visible(false);
    term::set_echo_mode(false);
    term::set_canonical_mode(false);

    size = term::get_size();
    buf = new Cell[size.area()];
}
void render::cleanup(){
    term::reset_color();
    term::set_canonical_mode(true);
    term::set_echo_mode(true);
    term::set_cursor_visible(true);
    term::set_alt_buf(false);

    if(buf)
        delete[] buf;
}

void render::update() {
    Point new_size = term::get_size();

    if(new_size != size){
        size = new_size;
        if(buf)
            delete[] buf;
        buf = new Cell[size.area()];
    }

    for(size_t i = 0; i < size.area(); i++){
        Cell& cell = buf[i];
        if(!cell.changed)
            continue;

        if(brush_fg != cell.fg){
            brush_fg = cell.fg;
            term::set_fg_color(brush_fg);
        }
        if(brush_bg != cell.bg){
            brush_bg = cell.bg;
            term::set_bg_color(brush_bg);
        }
        term::set_position(Point(i % size.x, i / size.x));
        term::write(cell.ch);
        cell.changed = false;
    }
}
