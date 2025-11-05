cmake_minimum_required(VERSION 4.1)
project(painter)
include_directories(src)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/render/term.cpp            src/render/term.h
    src/render/render.cpp          src/render/render.h
    src/render/obj/update_state.h
    src/render/obj/cell.cpp        src/render/obj/cell.h
    src/render/obj/pixel.cpp       src/render/obj/pixel.h
    src/core/point.cpp             src/core/point.h
    src/core/rgb.cpp               src/core/rgb.h
    src/core/tps_controller.cpp    src/core/tps_controller.h
)
