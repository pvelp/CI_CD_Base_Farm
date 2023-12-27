cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "3" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(CI_CD_FARM VERSION ${PROJECT_VERSION})

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)

configure_file(version.h.in version.h)

# file(READ "build/version.h" VERSION_FILE)
# string(REGEX MATCH "PROJECT_VERSION_PATCH ([0-9]*)" _ ${VERSION_FILE})
# set(PROJECT_VERSION_PATCH ${CMAKE_MATCH_1})
# math(EXPR PROJECT_VERSION_PATCH "${PROJECT_VERSION_PATCH} + 1")
# configure_file(version.h.in version.h @ONLY)

add_executable(main main.cpp)
add_library(lib lib.cpp)
target_link_libraries(main lib)

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
add_executable(tests ${TEST_SRC_FILES})
target_link_libraries(tests gtest gtest_main)
target_link_libraries(tests lib)
add_test(UnitTests tests)

set_target_properties(main tests lib PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_include_directories(lib
    PUBLIC ${CMAKE_CURRENT_DIR}/googletest
)

set(CPACK_GENERATOR DEB)

install(TARGETS main RUNTIME DESTINATION bin)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)