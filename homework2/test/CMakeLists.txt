cmake_minimum_required (VERSION 3.1)

project(test_homework2)

#find_package(GTest REQUIRED)

include(${GTEST_ROOT}/lib/cmake/GTest/GTestTargets.cmake)

set(HDRS )
         
set(SRCS 
    main.cpp
    ListPoolControlBlock.cpp
    PoolAllocator.cpp
    PoolControlBlock.cpp
)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ../include/
    ${GTEST_INCLUDE_DIRS}
)

# find_library (GMOCK_LIBRARIES 
# NAMES gmock 
# PATHS "${GTEST_ROOT}/lib" 
#    NO_DEFAULT_PATH)

target_link_libraries(${PROJECT_NAME}
#    ${GTEST_LIBRARIES} 
#    ${GMOCK_LIBRARIES}
    GTest::gtest
    GTest::gmock
    pthread
)

add_test(${PROJECT_NAME} ${PROJECT_NAME})