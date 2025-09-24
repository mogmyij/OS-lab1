cmake_minimum_required(VERSION 3.18)

project(EDA093-lab1 LANGUAGES C)

include_directories(/opt/homebrew/opt/readline/include)

add_executable(lsh parse.c lsh.c exec.c)
target_link_libraries(lsh PRIVATE /opt/homebrew/opt/readline/lib/libreadline.dylib ncurses)
target_compile_options(lsh PRIVATE "-ggdb3" "-O0" "-Wall" "-Wextra")
