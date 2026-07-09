add_executable(
        UnitTests
        UnitTests.cpp
        ../Clock.cpp
)

target_include_directories(UnitTests PRIVATE
        ../src/code/headers
)

target_link_libraries(
        UnitTests
        PRIVATE
        GTest::gtest_main
        SFML::Audio
        SFML::System
)

include(GoogleTest)
gtest_discover_tests(UnitTests)