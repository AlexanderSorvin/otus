cmake_minimum_required (VERSION 3.1)

project(homework1_task1_test)

find_package(Boost COMPONENTS unit_test_framework regex REQUIRED)

set(HDRS ../include/version.hpp)
         
set(SRCS main.cpp ../version.cpp)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../include/
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
)

enable_testing()

add_test(homework1 ${PROJECT_NAME})