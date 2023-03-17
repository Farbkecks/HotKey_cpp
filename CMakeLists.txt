if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

cmake_minimum_required(VERSION 3.24)

project (HotKey)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG c4713a704ca12237485ecbfec185f76c2a81bd09) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)


set(CMAKE_CXX_STANDARD 17)

add_executable(HotKey main.cpp)
target_link_libraries(HotKey PRIVATE cpr::cpr)



