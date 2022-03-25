cmake_minimum_required(VERSION 3.21)
project(MBition)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(MBition main.cpp parser.h parser.cpp)
target_link_libraries(MBition gtest_main)

# set up tests
enable_testing()

add_executable(tests UnitTests/GUnitTests.cpp parser.h parser.cpp)
target_link_libraries(tests gtest_main)
add_test(ParserTests tests)