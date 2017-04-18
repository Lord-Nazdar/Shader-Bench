cmake_minimum_required (VERSION 2.8.11)
project(ShaderBench)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

find_package(OpenGL REQUIRED)

add_subdirectory(3rdparty/glfw)

file(GLOB_RECURSE sources src/*.cpp src/*.h)
set(lodepng_src 3rdparty/lodepng/lodepng.cpp)

add_executable(app ${sources} ${lodepng_src})

set_target_properties(app PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ../res)

target_compile_definitions(app PRIVATE Sirona_Graphics_Interface)
target_compile_definitions(app PRIVATE _HAS_EXCEPTIONS=0 _HAS_ITERATOR_DEBUGGING=0 _SCL_SECURE=0 _SECURE_SCL=0 _SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS _CRT_SECURE_NO_DEPRECATE BGFX_CONFIG_DEBUG=1)

target_link_libraries(app glfw)
target_link_libraries(app opengl32)
target_link_libraries(app ..\\3rdparty\\bgfx\\.build\\win32_vs2015\\bin\\bgfxDebug)
target_link_libraries(app ../3rdparty/bgfx/.build/win32_vs2015/bin/bxDebug)
target_link_libraries(app ../3rdparty/bgfx/.build/win32_vs2015/bin/bimgDebug)

target_include_directories(app PUBLIC 3rdparty/imgui)
target_include_directories(app PUBLIC 3rdparty/lodepng)
target_include_directories(app PUBLIC 3rdparty/glm/glm)
target_include_directories(app PUBLIC 3rdparty/tinyobjloader)
target_include_directories(app PUBLIC 3rdparty/glfw/include)
target_include_directories(app PUBLIC 3rdparty/bgfx/include)
target_include_directories(app PUBLIC 3rdparty/bx/include)