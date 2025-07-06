cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DearImKit VERSION 1.0 LANGUAGES C CXX)

add_subdirectory(extern/glfw3)

file(GLOB IMGUI_BACKEND ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp)
file(GLOB IMGUI_SOURCES ${PROJECT_SOURCE_DIR}/extern/imgui/*.cpp ${PROJECT_SOURCE_DIR}/extern/imgui/misc/cpp/imgui_stdlib.cpp)

add_library(imgui ${IMGUI_BACKEND} ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR}/extern/imgui)

target_link_libraries(imgui PRIVATE glfw)

file(GLOB_RECURSE LIB_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/lib/*.c ${PROJECT_SOURCE_DIR}/lib/*.cpp)

add_library(lib ${LIB_FILES})
target_include_directories(lib PUBLIC ${PROJECT_SOURCE_DIR}/lib/include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

if(DEARIMKIT_BUILD_SHARED)
    add_library(DearImKit SHARED ${SOURCES})
else()
    add_library(DearImKit STATIC ${SOURCES})
endif()

target_include_directories(DearImKit PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(DearImKit PRIVATE lib glfw PUBLIC imgui)