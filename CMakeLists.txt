cmake_minimum_required(VERSION 3.16)
project(ParserOpenFlight LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/ParserOpenFlight/include)

add_executable(${PROJECT_NAME}
    ParserOpenFlight/Main.cpp
    ParserOpenFlight/src/ParserOpenFlight.cpp
)