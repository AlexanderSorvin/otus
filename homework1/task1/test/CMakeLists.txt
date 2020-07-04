cmake_minimum_required (VERSION 3.1)

project(test_homework1_task1)

# Boost, когда собирает статические библиотеки, добавляет в название x64 или x32.
# При этом, эти названия он не ищет. Что я мог сделать не так?
# Пробовал задать address-model=64, но не помогло
# Пришлось отредактировать названия библиотек.
find_package(Boost COMPONENTS unit_test_framework regex REQUIRED)

set(HDRS ../include/version.hpp)
         
set(SRCS main.cpp ../version.cpp)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../include/
    ${Boost_INCLUDE_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_link_libraries(${PROJECT_NAME}
    ${Boost_LIBRARIES}
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})