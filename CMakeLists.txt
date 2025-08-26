cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DearImKit VERSION 1.0 LANGUAGES C CXX)

set(GLFW_INSTALL OFF)
add_subdirectory(extern/glfw3)

file(GLOB IMGUI_BACKEND ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp ${PROJECT_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp)
file(GLOB IMGUI_SOURCES ${PROJECT_SOURCE_DIR}/extern/imgui/*.cpp ${PROJECT_SOURCE_DIR}/extern/imgui/misc/cpp/imgui_stdlib.cpp)

add_library(imgui OBJECT ${IMGUI_BACKEND} ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/extern/imgui>
)

# message(${IMGUI_SOURCES})

# target_link_libraries(imgui PRIVATE glfw)

file(GLOB_RECURSE LIB_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/lib/*.c ${PROJECT_SOURCE_DIR}/lib/*.cpp)

add_library(thirdparty ${LIB_FILES})
target_include_directories(thirdparty PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/lib/include>
)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE DEARIMKIT_SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp)

if(DEARIMKIT_BUILD_SHARED)
    add_library(dearimkit SHARED ${DEARIMKIT_SOURCES} $<TARGET_OBJECTS:imgui>)
    # add_library(dearimkit SHARED ${DEARIMKIT_SOURCES})
    set_target_properties(imgui PROPERTIES POSITION_INDEPENDENT_CODE ON EXCLUDE_FROM_ALL ON)
    set_target_properties(thirdparty PROPERTIES POSITION_INDEPENDENT_CODE ON EXCLUDE_FROM_ALL ON)
else()
    add_library(dearimkit STATIC ${DEARIMKIT_SOURCES} $<TARGET_OBJECTS:imgui>)
    # add_library(dearimkit SHARED ${DEARIMKIT_SOURCES})
endif()

target_include_directories(dearimkit PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)
target_link_libraries(dearimkit PRIVATE thirdparty glfw OpenGL::GL)
target_include_directories(dearimkit PUBLIC
    $<TARGET_PROPERTY:imgui,INTERFACE_INCLUDE_DIRECTORIES>
)

if(DEARIMKIT_INSTALL_LOCATION)
    install(
        TARGETS dearimkit imgui glfw thirdparty
        ARCHIVE DESTINATION ${DEARIMKIT_INSTALL_LOCATION}
        LIBRARY DESTINATION ${DEARIMKIT_INSTALL_LOCATION}
    )
elseif(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    if(UNIX)
        set(CMAKE_INSTALL_PREFIX /usr/local/)
        set(INCLUDE_LOCATION /usr/local/include)
        # target_include_directories(imgui INTERFACE $<INSTALL_INTERFACE:${INCLUDE_LOCATION}>)
        target_include_directories(dearimkit INTERFACE $<INSTALL_INTERFACE:${INCLUDE_LOCATION}>)
    elseif(WIN32)
        set(CMAKE_INSTALL_PREFIX ${DEARIMKIT_INSTALL_LOCATION})
    endif()
    install(
        TARGETS dearimkit imgui glfw thirdparty
        EXPORT dearimkitTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
    )
    install(
        EXPORT dearimkitTargets
        FILE ConfigDearImKit.cmake
        NAMESPACE DearImKit::
        DESTINATION lib/XYZcmake
    )
endif()
