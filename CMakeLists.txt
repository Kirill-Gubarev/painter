cmake_minimum_required(VERSION 4.1)
project(painter)
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/term.cpp        src/term.h
    src/render.cpp      src/render.h

    src/core/point.cpp  src/core/point.h
    src/core/rgb.cpp    src/core/rgb.h
)
