cmake_minimum_required(VERSION 3.17)
project(next_gis)

set(CMAKE_CXX_STANDARD 14)

set(ROOT ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT}/build)
set(3RD_PARTY_DIR ${ROOT}/third_party)
message(STATUS "third_party - " ${3RD_PARTY_DIR})

# glfw
set(GLFW_INCLUDE ${3RD_PARTY_DIR}/glfw/include)
set(GLFW_LINK ${3RD_PARTY_DIR}/glfw/lib)
include_directories(${GLFW_INCLUDE})
link_directories(${GLFW_LINK})
link_libraries(glfw3)

find_package(OpenGL REQUIRED)

# glad
set(GLAD_INCLUDE ${3RD_PARTY_DIR}/glad/include)
set(GLAD_LINK ${3RD_PARTY_DIR}/glad/src)
include_directories(${GLAD_INCLUDE})

## imgui
set(IMGUI_DIR ${3RD_PARTY_DIR}/imgui)
add_library(imgui
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_internal.h
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui.h
        ${IMGUI_DIR}/imconfig.h
        ${IMGUI_DIR}/imgui_impl_glfw.h
        ${IMGUI_DIR}/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/imgui_impl_opengl3.h
        ${IMGUI_DIR}/imgui_impl_opengl3.cpp
        ${IMGUI_DIR}/imstb_truetype.h
        )
target_include_directories(imgui PUBLIC ${IMGUI_DIR})

if (APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(COREVIDEO_LIBRARY CoreVideo)
    SET(EXTRA_LIBS ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
endif (APPLE)

if (WIN32)
    # no content
endif ()

file(GLOB_RECURSE INCLUDE_FILES ${ROOT}/include/*.h)
file(GLOB RECURSE SOURCE_FILES ${ROOT}/src/*.cpp)

set(SRC_FILES
        src/main.cpp
        ${GLAD_LINK}/glad.c
        ${INCLUDE_FILES}
        ${SOURCE_FILES}
        )


add_executable(next_gis ${SRC_FILES})
target_link_libraries(next_gis glfw3 imgui ${EXTRA_LIBS} ${OPENGL_LIBRARIES})