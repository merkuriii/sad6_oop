# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Lab6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    main.cpp
    src/npc.cpp
    src/SlaveTrader.cpp
    src/Squirrel.cpp
    src/Knight.cpp
    src/Factory.cpp
    src/PrintVisitor.cpp
    src/Observer.cpp
    src/World.cpp
)

# Main executable
add_executable(main ${SOURCES})

# Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test executable
add_executable(tests
    test/test.cpp
    src/npc.cpp
    src/SlaveTrader.cpp
    src/Squirrel.cpp
    src/Knight.cpp
    src/Factory.cpp
    src/PrintVisitor.cpp
    src/Observer.cpp
    src/World.cpp
)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)
add_test(NAME UnitTests COMMAND tests)