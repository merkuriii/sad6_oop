cmake_minimum_required(VERSION 3.14)
project(lab6)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(funcs
    src/main.cpp
    src/BattleLogger.cpp
    src/BattleVisitor.cpp
    src/ConsoleObserver.cpp
    src/Knight.cpp
    src/DungeonEditor.cpp
    src/Factory.cpp
    src/FileObserver.cpp
    src/npc.cpp
    src/Squirrel.cpp
    src/WorkerTrader.cpp
)

target_include_directories(funcs PRIVATE include)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

add_executable(tests test/test6.cpp)
target_include_directories(tests PRIVATE include)
target_link_libraries(tests GTest::gtest_main)

enable_testing()
add_test(NAME Tests COMMAND tests)