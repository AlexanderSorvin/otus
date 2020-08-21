cmake_minimum_required (VERSION 3.1)

project(test_homework4)

find_package(Threads)

find_package(GTest CONFIG REQUIRED)

set(HDRS )
         
set(SRCS 
    main.cpp
)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../include/
)

target_link_libraries(${PROJECT_NAME}
    GTest::gtest
    GTest::gmock
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})