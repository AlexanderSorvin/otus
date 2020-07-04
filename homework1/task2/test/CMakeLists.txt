cmake_minimum_required (VERSION 3.1)

project(homework1_task2_test)

find_package(GTest REQUIRED)

set(HDRS ../include/ipv4.hpp)
         
set(SRCS main.cpp ipv4.cpp ../src/ipv4.cpp)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../include/
    ${GTEST_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES}
)

enable_testing()

add_test(homework1 ${PROJECT_NAME})