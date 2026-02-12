cmake_minimum_required(VERSION 4.0)
project(04AI_FIR)

# 查找 SDL2 库
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

# 添加可执行文件
add_executable(04AI_FIR
        src/ai_judge.c
        src/display.c
        src/input_storage.c
        src/main.c
)

# 包含目录
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

# 链接库
target_link_libraries(04AI_FIR ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} m)

target_include_directories(04AI_FIR PRIVATE inc)