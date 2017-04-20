cmake_minimum_required (VERSION 2.8.11)
project(ShaderBench)

set(sb_graphics_interface Sirona_Graphics_Interface CACHE STRING Define which grahpics interface will be used)

# Only generate on win32 targets
if( NOT WIN32 )
    message( FATAL_ERROR, "ShaderBench is only available on Win32 systems")
endif()

message(STATUS "Running bgfx genie...")

set(genie_location ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bx/tools/bin/)
if( WIN32 )
    set(genie_exec windows/genie)

    if( MSVC_VERSION EQUAL 1900)
        set(genie_arg vs2015)
    endif()
endif()

execute_process(COMMAND ${genie_location}${genie_exec} ${genie_arg} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx OUTPUT_VARIABLE bgfx_out)
message(STATUS "${bgfx_out}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Force runtime library to debug and no dll (bgfx requirement)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

message(STATUS "Adding glfw...")
# Force runtime library as well for glfw
set(USE_MSVC_RUNTIME_LIBRARY_DLL OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(3rdparty/glfw)

# Adding sources
file(GLOB_RECURSE sources src/*.cpp src/*.h)
set(lodepng_src 3rdparty/lodepng/lodepng.cpp)

add_executable(ShaderBench ${sources} ${lodepng_src})

# Add genie generated projects
if( MSVC )
    include_external_msproject(bgfx ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx/.build/projects/vs2015/bgfx.vcxproj)
    set_target_properties(bgfx PROPERTIES FOLDER "BGFX")

    include_external_msproject(bx ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx/.build/projects/vs2015/bx.vcxproj)
    set_target_properties(bx PROPERTIES FOLDER "BGFX")

    include_external_msproject(bimg ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx/.build/projects/vs2015/bimg.vcxproj)
    set_target_properties(bimg PROPERTIES FOLDER "BGFX")
endif()

add_dependencies(ShaderBench bgfx bx bimg)

# Set debugger working directory and startup project on msvc
if( MSVC )
    set_target_properties(ShaderBench PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/res)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ShaderBench)
endif()

target_compile_definitions(ShaderBench PRIVATE ${sb_graphics_interface})

# Multiple preprocessors added for bgfx
target_compile_definitions(ShaderBench PRIVATE _HAS_EXCEPTIONS=0 _HAS_ITERATOR_DEBUGGING=0 _SCL_SECURE=0 _SECURE_SCL=0 _SCL_SECURE_NO_WARNINGS _CRT_SECURE_NO_WARNINGS _CRT_SECURE_NO_DEPRECATE BGFX_CONFIG_DEBUG=1)

# Adding remaining dependencies
target_link_libraries(ShaderBench glfw)
target_link_libraries(ShaderBench opengl32)
target_link_libraries(ShaderBench ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx/.build/win32_vs2015/bin/bgfxDebug.lib)
target_link_libraries(ShaderBench ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx/.build/win32_vs2015/bin/bxDebug.lib)
target_link_libraries(ShaderBench ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx/.build/win32_vs2015/bin/bimgDebug.lib)

target_include_directories(ShaderBench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/imgui)
target_include_directories(ShaderBench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/lodepng)
target_include_directories(ShaderBench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm/glm)
target_include_directories(ShaderBench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/tinyobjloader)
target_include_directories(ShaderBench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfw/include)
target_include_directories(ShaderBench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bgfx/include)
target_include_directories(ShaderBench PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/bx/include)