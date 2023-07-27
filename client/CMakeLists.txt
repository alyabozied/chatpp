cmake_minimum_required(VERSION 3.0)
project(chatclient)
file(GLOB src  "*.cpp" "../src/*.cpp")
include_directories(${PROJECT_SOURCE_DIR}/../src/include)

add_executable(chatclient ${src})
target_link_libraries(chatclient ncurses)