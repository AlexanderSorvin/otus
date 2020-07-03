cmake_minimum_required (VERSION 3.1)

project(homework1_task2)

set(HDRS include/ipv4.hpp)
         
set(SRCS src/main.cpp src/ipv4.cpp)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    include/
    ${GTEST_INCLUDE_DIRS}
)

add_subdirectory(test)