cmake_minimum_required (VERSION 3.1)

project(homework2 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(HDRS 
    include/allocator/ListPoolControlBlock.hpp
    include/allocator/PoolAllocator.hpp
    include/allocator/PoolControlBlock.hpp
    include/vector/CustomVector.hpp
)
         
set(SRCS 
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME} PRIVATE 
    include/
)

enable_testing()

add_subdirectory(test)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)