#include "term.h"
#include "render.h"
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
    for(char ch; (ch = term::get_char());){
        if(ch == 'q')
            break;
        render::update();
    }
    render::cleanup();

    return 0;
}
