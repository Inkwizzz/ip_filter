cmake_minimum_required(VERSION 3.29)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.1.${PATCH_VERSION})

project(Allocator_cmake VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

add_executable(Allocator_cmake_cli Allocator_cmake.cpp)

set_target_properties(Allocator_cmake_cli PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(Allocator_cmake_cli
        PRIVATE "${CMAKE_BINARY_DIR}"
)


if (MSVC)
    target_compile_options(Allocator_cmake_cli PRIVATE /W4)
else()
    target_compile_options(Allocator_cmake_cli PRIVATE -Wall -Wextra -pedantic)
endif()

install(TARGETS Allocator_cmake_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)