cmake_minimum_required (VERSION 2.6)

project (Gistory CXX)

cmake_policy(SET CMP0015 NEW)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories (dependencies)

add_executable (
    Gistory
    gistory.cpp
    RepoManager.cpp
)

target_link_libraries (
    Gistory
    git2
)

add_custom_command(
    TARGET Gistory POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/dependencies/git2.dll
    ${CMAKE_BINARY_DIR}/git2.dll
)
