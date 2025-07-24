cmake_minimum_required(VERSION 3.10)
project(TrickyTowers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем CMake где искать SFML
set(SFML_ROOT "C:/SFML-3.0.0")  

# Ищем SFML
find_package(SFML 3.0.0 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    message(STATUS "SFML found: ${SFML_DIR}")
else()
    message(FATAL_ERROR "SFML not found!")
endif()

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(TrickyTowers ${SOURCES})

target_link_libraries(ed.project 
    sfml-graphics 
    sfml-window 
    sfml-system)
