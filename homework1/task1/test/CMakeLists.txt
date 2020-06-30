cmake_minimum_required (VERSION 3.1)

project(homework1_test)

#set(HDRS )
         
set(SRCS main.cpp)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

include_directories(../include/)