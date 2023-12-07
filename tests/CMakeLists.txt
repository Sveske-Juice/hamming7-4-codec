cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)

# Include all unit tests
file(GLOB_RECURSE SRC_FILES *.cpp)
add_executable(tests ${SRC_FILES})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
