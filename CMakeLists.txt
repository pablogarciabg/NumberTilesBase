cmake_minimum_required(VERSION 3.22)
project(NumberTilesBase)

set(CMAKE_CXX_STANDARD 14)

set(MSYS2_PATH "C:/msys64/mingw64")

# Incluye los encabezados de Allegro
include_directories(src)
include_directories(${MSYS2_PATH}/include/allegro5)

# Vincula las bibliotecas de Allegro
link_directories(${MSYS2_PATH}/lib)

file(GLOB LIBRARIES "${MSYS2_PATH}/lib/*.dll.a")
message("LIBRARIES = ${LIBRARIES}")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out)
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")

add_executable(NumberTilesBase
    src/entorno.cpp
    src/entorno.h
    src/numberTiles.cpp
    src/NumberTiles.h)

TARGET_LINK_LIBRARIES(NumberTilesBase  allegro_acodec
        allegro_audio
        allegro_color
        allegro_dialog
        allegro_image
        allegro_main
        allegro_memfile
        allegro_physfs
        allegro_primitives
        allegro_ttf
        allegro_font
        allegro)