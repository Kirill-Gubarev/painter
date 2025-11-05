#include "cell.h"

render::detail::Cell::Cell(wchar_t glyph, const core::RGB& fg,
        const core::RGB& bg, Update_state update):
    glyph(glyph),
    fg(fg),
    bg(bg),
    update(update)
{}
bool render::detail::operator==(const Cell& c1, const Cell& c2){
    return c1.glyph == c2.glyph && c1.fg == c2.fg && c1.bg == c2.bg;
}
bool render::detail::operator!=(const Cell& c1, const Cell& c2){
    return c1.glyph != c2.glyph || c1.fg != c2.fg || c1.bg != c2.bg;
}
