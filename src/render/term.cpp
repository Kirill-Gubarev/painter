#include "term.h"

#include <cwchar>
#include <cstdio>
#include <clocale>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

namespace term{
    static struct{
        core::RGB default_fg = core::RGB(255);
        core::RGB default_bg = core::RGB(0);
    } state;
}

char term::get_char(){
    return getchar();
}

core::Point term::get_size(){
    winsize w;
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1)
        return {};
    return core::Point(w.ws_col, w.ws_row);
}
core::RGB term::get_default_fg(){
    return state.default_fg;
}
core::RGB term::get_default_bg(){
    return state.default_bg;
}

void term::write(wchar_t glyph){
    wprintf(L"%lc", glyph);
}
void term::write(const wchar_t* str){
    wprintf(L"%ls", str);
}

void term::set_fg_color(const core::RGB& c){
    wprintf(L"\033[38;2;%u;%u;%um", c.r, c.g, c.b);
}
void term::set_bg_color(const core::RGB& c){
    wprintf(L"\033[48;2;%u;%u;%um", c.r, c.g, c.b);
}
void term::set_position(const core::Point& new_pos){
    wprintf(L"\033[%d;%dH", new_pos.y + 1, new_pos.x + 1);
}

void term::set_alt_buf(bool enable){
    if(enable)
        term::write(L"\033[?1049h");
    else
        term::write(L"\033[?1049l");
}
void term::set_cursor_visible(bool enable){
    if(enable)
        term::write(L"\033[?25h");
    else
        term::write(L"\033[?25l");
}
void term::set_echo_mode(bool enable){
    termios mode;
    tcgetattr(STDIN_FILENO, &mode);
    if(enable)
        mode.c_lflag |= ECHO;
    else
        mode.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &mode);
}
void term::set_canonical_mode(bool enable){
    termios mode;
    tcgetattr(STDIN_FILENO, &mode);
    if(enable)
        mode.c_lflag |= ICANON;
    else
        mode.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &mode);
}
void term::set_locale(){
    std::setlocale(LC_ALL,"");
}

void term::reset_color(){
    wprintf(L"\033[0m");
}
void term::clear(){
    term::set_fg_color(state.default_fg);
    term::set_bg_color(state.default_bg);
    term::write(L"\033[2J");
}
