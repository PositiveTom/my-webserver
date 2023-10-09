cmake_minimum_required(VERSION 3.26)
project(webserver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

set(ALL_SRC "")
list(APPEND ALL_SRC 
    src/server/ioselecthandler.cc
    src/server/server.cc
    src/threadpool/threadpool.cc
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(${PROJECT_NAME} SHARED ${ALL_SRC})

add_executable(main main.cpp)
target_link_libraries(main ${PROJECT_NAME})
