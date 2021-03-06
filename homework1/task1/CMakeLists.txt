cmake_minimum_required (VERSION 3.1)

set(PROJECT_BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER})

project(homework1_task1 VERSION 0.0.${PROJECT_BUILD_NUMBER})

configure_file(src/version.cpp.in version.cpp)

set(HDRS include/version.hpp)         
set(SRCS src/main.cpp version.cpp)

add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE 
    include/)

enable_testing()

add_subdirectory(test)

install(TARGETS homework1_task1 RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)