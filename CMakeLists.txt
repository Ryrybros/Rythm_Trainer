cmake_minimum_required(VERSION 3.28)
project(Rythm_Trainer LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 1. Fetch SFML 3 from GitHub automatically
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.1.0 # Or 'master' depending on your template
)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/code/headers/Clock.h
        src/code/Clock.cpp)
target_compile_features(main PRIVATE cxx_std_17)

target_link_libraries(main PRIVATE 
    SFML::Graphics
    SFML::Audio
    SFML::Window
    SFML::System
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)