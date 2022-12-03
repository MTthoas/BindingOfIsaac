# Define the project name

project(BindingOfIsaac)

cmake_minimum_required(VERSION 3.5.1)

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/sdl2)

file(GLOB SOURCES "sources/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE sources/include)

target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror >)


set(CMAKE_C_FLAGS -pthread)
