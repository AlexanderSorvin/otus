cmake_minimum_required (VERSION 3.1)

project(test_homework1_task2)

find_package(GTest REQUIRED)

set(HDRS ../include/ipv4.hpp)
         
set(SRCS main.cpp ipv4.cpp ../src/ipv4.cpp)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../include/
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})