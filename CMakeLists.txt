cmake_minimum_required(VERSION 4.2)
project(backuprythm)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        3.1.0 # Or 'master' depending on your template
)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(SFML googletest)

enable_testing()
add_subdirectory(tests)

add_executable(backuprythm main.cpp
        Clock.cpp
        Clock.h
        RhythmMaker.cpp
        RhythmMaker.h)


target_link_libraries(backuprythm PRIVATE
        SFML::Graphics
        SFML::Audio
        SFML::Window
        SFML::System
)
