cmake_minimum_required(VERSION 3.15)
project(3D_Object_Viewer)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(3D_Object_Viewer
        main.cpp
        Mesh.cpp
        Mesh.h
        Shader.cpp
        Shader.h
        Window.cpp
        Window.h
)

target_include_directories(3D_Object_Viewer PRIVATE "C:/dev/vcpkg/installed/x64-mingw-dynamic/include")
target_link_libraries(3D_Object_Viewer PRIVATE glad::glad glfw)
