cmake_minimum_required(VERSION 3.24)
project(raymarcher)
message("CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}")
message("CMAKE_OBJDUMP = ${CMAKE_OBJDUMP}")

SET(CMAKE_CXX_FLAGS_FAST "-Ofast")
SET(CMAKE_C_FLAGS_FAST "-Ofast")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# By default take the SDL installation paths from environment variables, feel free to override them if you like
set(SDL2_INCLUDE_DIR $ENV{SDL2_INCLUDE_DIR})
set(SDL2_LIBRARY_DIR $ENV{SDL2_LIBRARY_DIR})

if (WIN32)
    set(EXECUTABLE_BINARY_EXTENSION ".exe")
else()
    set(EXECUTABLE_BINARY_EXTENSION ".elf")
endif()

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
        src/scenes/all.h
        src/materialE.h
        src/cppTrickery/lut.h
        src/scenes/scene.h
        src/scenes/scene.h)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

#target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")

add_custom_command(
        OUTPUT ${CMAKE_PROJECT_NAME}.lst
        MAIN_DEPENDENCY $<TARGET_FILE:${CMAKE_PROJECT_NAME}.${EXECUTABLE_BINARY_EXTENSION}>
        COMMAND ${CMAKE_OBJDUMP} -h -S $<TARGET_FILE:${CMAKE_PROJECT_NAME}.${EXECUTABLE_BINARY_EXTENSION}> > ${CMAKE_PROJECT_NAME}.lst
        COMMENT "Invoking: Create Listing")

if (LINUX)
    #target_link_libraries(raymarcher mingw32 SDL2main SDL2)
    target_link_libraries(${CMAKE_PROJECT_NAME} SDL2main SDL2)
endif()

if (WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME} mingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a ${SDL2_LIBRARY_DIR}/libSDL2.dll.a)
endif()

