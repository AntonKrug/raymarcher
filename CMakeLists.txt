cmake_minimum_required(VERSION 3.19)
project(raymarcher)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        src/main.cpp src/color.cpp src/color.h src/vector.cpp src/vector.h src/sampler.cpp src/sampler.h src/config.h src/rayMarcher.cpp src/rayMarcher.h src/outputSdl.cpp src/outputSdl.h src/helper.cpp src/helper.h src/signedDistance.cpp src/signedDistance.h src/scenes/mhcp.cpp src/scenes/mhcp.h src/cppTrickery/floatInt.cpp src/cppTrickery/floatInt.h src/scenes/all.h)

add_executable(raymarcher ${SOURCE_FILES})

target_link_libraries(raymarcher mingw32 SDL2main SDL2 SDL2_image)
