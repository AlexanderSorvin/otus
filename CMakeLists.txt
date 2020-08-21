cmake_minimum_required (VERSION 3.1)

project(OTUS)

set(ENV{TRAVIS_BUILD_NUMBER} 1)

if (MSVC)
    add_compile_options(/W4)
else ()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

enable_testing()

add_subdirectory(homework1)
add_subdirectory(homework2)
add_subdirectory(homework3)
add_subdirectory(homework4)