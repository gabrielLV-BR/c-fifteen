cmake_minimum_required(VERSION 3.17)
project(fifteen VERSION 1.0)

find_library(REQUIRED raylib)

add_executable(
	${PROJECT_NAME}
	src/main.c
)

target_include_directories(${PROJECT_NAME} PRIVATE modules/raylib/src/)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
