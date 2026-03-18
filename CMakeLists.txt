cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DearImKit VERSION 1.0 LANGUAGES C CXX)


#################### SETUP OPTIONS ####################

option(DEARIMKIT_BUILD_SHARED "Build as Shared Library" OFF)


#################### GATHER DEPENDENCIES ####################

set(GLFW_INSTALL OFF)
add_subdirectory(extern/glfw3)

file(GLOB IMGUI_BACKEND ${PROJECT_SOURCE_DIR}/extern/cimgui/imgui/backends/imgui_impl_glfw.cpp ${PROJECT_SOURCE_DIR}/extern/cimgui/imgui/backends/imgui_impl_opengl3.cpp)
file(GLOB IMGUI_SOURCES ${PROJECT_SOURCE_DIR}/extern/cimgui/imgui/*.cpp ${PROJECT_SOURCE_DIR}/extern/cimgui/imgui/misc/cpp/imgui_stdlib.cpp)
file(GLOB CIMGUI_SOURCES ${PROJECT_SOURCE_DIR}/extern/cimgui/cimgui.cpp)

add_library(cimgui OBJECT ${IMGUI_BACKEND} ${IMGUI_SOURCES} ${CIMGUI_SOURCES})
target_include_directories(cimgui PRIVATE ${PROJECT_SOURCE_DIR}/extern/cimgui)
target_include_directories(cimgui PRIVATE ${PROJECT_SOURCE_DIR}/extern/cimgui/imgui)
target_include_directories(cimgui INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/extern/cimgui>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/extern/cimgui/imgui>
    $<INSTALL_INTERFACE:include/DearImKit/cimgui>
)

target_link_libraries(cimgui PRIVATE glfw)

file(GLOB_RECURSE LIB_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/lib/*.c ${PROJECT_SOURCE_DIR}/lib/*.cpp)

add_library(thirdparty OBJECT ${LIB_FILES})
target_include_directories(thirdparty PUBLIC ${PROJECT_SOURCE_DIR}/lib/include)

find_package(OpenGL REQUIRED)


#################### GATHER DEARIMKIT SOURCES ####################

file(GLOB_RECURSE DEARIMKIT_SOURCES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/c/*.cpp)


#################### BUILD DEARIMKIT LIBRARY ####################

if(DEARIMKIT_BUILD_SHARED)
    add_library(dearimkit SHARED ${DEARIMKIT_SOURCES} $<TARGET_OBJECTS:cimgui> $<TARGET_OBJECTS:thirdparty>)
    set_target_properties(cimgui PROPERTIES POSITION_INDEPENDENT_CODE ON EXCLUDE_FROM_ALL ON)
    set_target_properties(thirdparty PROPERTIES POSITION_INDEPENDENT_CODE ON EXCLUDE_FROM_ALL ON)
else()
    add_library(dearimkit STATIC ${DEARIMKIT_SOURCES} $<TARGET_OBJECTS:cimgui> $<TARGET_OBJECTS:thirdparty>)
endif()


#################### SETUP DEARIMKIT HEADERS ####################

target_include_directories(dearimkit PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(dearimkit PRIVATE
    $<TARGET_PROPERTY:cimgui,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(dearimkit PRIVATE
    $<TARGET_PROPERTY:thirdparty,INTERFACE_INCLUDE_DIRECTORIES>)
target_include_directories(dearimkit INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/c/include>)
target_include_directories(dearimkit INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)


#################### LINK LIBRARIES ####################

# target_link_options(dearimkit PRIVATE -static-libgcc -static-libstdc++)
target_link_libraries(dearimkit PRIVATE glfw OpenGL::GL)
target_include_directories(dearimkit INTERFACE
    $<TARGET_PROPERTY:cimgui,INTERFACE_INCLUDE_DIRECTORIES>
)


#################### INSTALL DEARIMKIT ####################

install(TARGETS dearimkit cimgui glfw
    EXPORT dearimkitTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(EXPORT dearimkitTargets
    NAMESPACE DearImKit::
    DESTINATION lib/cmake/DearImKit
)

install(FILES cmake/DearImKitConfig.cmake
    DESTINATION lib/cmake/DearImKit
)

install(DIRECTORY c/include/
    DESTINATION include
)

install(FILES extern/cimgui/cimgui.h 
    DESTINATION include/DearImKit/cimgui
)

# if(DEARIMKIT_INSTALL_LOCATION)
#     install(
#         TARGETS dearimkit imgui glfw thirdparty
#         ARCHIVE DESTINATION ${DEARIMKIT_INSTALL_LOCATION}
#         LIBRARY DESTINATION ${DEARIMKIT_INSTALL_LOCATION}
#     )
# elseif(PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
#     if(UNIX)
#         set(CMAKE_INSTALL_PREFIX /usr/local/)
#         set(INCLUDE_LOCATION /usr/local/include)
#         # target_include_directories(imgui INTERFACE $<INSTALL_INTERFACE:${INCLUDE_LOCATION}>)
#         target_include_directories(dearimkit INTERFACE $<INSTALL_INTERFACE:${INCLUDE_LOCATION}>)
#     elseif(WIN32)
#         set(CMAKE_INSTALL_PREFIX ${DEARIMKIT_INSTALL_LOCATION})
#     endif()
#     install(
#         TARGETS dearimkit imgui glfw thirdparty
#         EXPORT dearimkitTargets
#         ARCHIVE DESTINATION lib
#         LIBRARY DESTINATION lib
#         INCLUDES DESTINATION include
#     )
#     install(
#         DIRECTORY include
#         DESTINATION include
#     )
#     install(
#         EXPORT dearimkitTargets
#         FILE ConfigDearImKit.cmake
#         NAMESPACE DearImKit::
#         DESTINATION lib/cmake
#     )
# endif()
