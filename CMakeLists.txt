cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DearImKit VERSION 1.0 LANGUAGES C CXX)

set(GLFW_INSTALL OFF)
add_subdirectory(extern/glfw3)

file(GLOB IMGUI_BACKEND ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp)
file(GLOB IMGUI_SOURCES ${PROJECT_SOURCE_DIR}/extern/imgui/*.cpp ${PROJECT_SOURCE_DIR}/extern/imgui/misc/cpp/imgui_stdlib.cpp)

add_library(imgui ${IMGUI_BACKEND} ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR}/extern/imgui)

target_link_libraries(imgui PRIVATE glfw)

file(GLOB_RECURSE LIB_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/lib/*.c ${PROJECT_SOURCE_DIR}/lib/*.cpp)

add_library(lib ${LIB_FILES})
target_include_directories(lib PUBLIC ${PROJECT_SOURCE_DIR}/lib/include)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE DEARIMKIT_SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

if(DEARIMKIT_BUILD_SHARED)
    add_library(dearimkit SHARED ${DEARIMKIT_SOURCES})
    set_target_properties(imgui PROPERTIES POSITION_INDEPENDENT_CODE ON)
    set_target_properties(lib PROPERTIES POSITION_INDEPENDENT_CODE ON)
else()
    add_library(dearimkit STATIC ${DEARIMKIT_SOURCES})
endif()

if(DEARIMKIT_INSTALL_LOCATION)
    install(TARGETS dearimkit DESTINATION ${DEARIMKIT_INSTALL_LOCATION})
endif()

target_include_directories(dearimkit PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(dearimkit PRIVATE lib glfw OpenGL::GL PUBLIC imgui)