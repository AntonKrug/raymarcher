cmake_minimum_required(VERSION 3.19)
project(raymarcher)

SET(CMAKE_CXX_FLAGS_FAST "-Ofast")
SET(CMAKE_C_FLAGS_FAST "-Ofast")

set(CMAKE_CXX_STANDARD 17)

# By default take the SDL installation paths from environment variables, feel free to override them if you like
set(SDL2_INCLUDE_DIR $ENV{SDL2_INCLUDE_DIR})
set(SDL2_LIBRARY_DIR $ENV{SDL2_LIBRARY_DIR})

set(SOURCE_FILES
        src/main.cpp
        src/color.cpp
        src/color.h
        src/vector.cpp
        src/vector.h
        src/sampler.cpp
        src/sampler.h
        src/config.h
        src/rayMarcher.cpp
        src/rayMarcher.h
        src/outputSdl.cpp
        src/outputSdl.h
        src/helper.cpp
        src/helper.h
        src/signedDistance.cpp
        src/signedDistance.h
        src/scenes/mchp.cpp
        src/scenes/mchp.h
        src/cppTrickery/floatInt.cpp
        src/cppTrickery/floatInt.h
        src/scenes/all.h
        src/materialE.h
        src/cppTrickery/lut.h)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(raymarcher ${SOURCE_FILES})

#target_include_directories(raymarcher PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

if (LINUX)
    #target_link_libraries(raymarcher mingw32 SDL2main SDL2)
    target_link_libraries(raymarcher SDL2main SDL2)
endif()

if (WIN32)
    target_link_libraries(raymarcher mingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a ${SDL2_LIBRARY_DIR}/libSDL2.dll.a)
endif()