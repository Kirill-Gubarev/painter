cmake_minimum_required(VERSION 4.1)
project(painter)
include_directories(src)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/term.cpp           src/term.h
    src/render/render.cpp  src/render/render.h
    src/render/cell.cpp    src/render/cell.h
    src/render/pixel.cpp   src/render/pixel.h
    src/core/point.cpp     src/core/point.h
    src/core/rgb.cpp       src/core/rgb.h
)
