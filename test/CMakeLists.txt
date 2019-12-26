add_library(kitsune-twain++-testbase INTERFACE)
target_link_libraries(kitsune-twain++-testbase INTERFACE twain++)
target_include_directories(kitsune-twain++-testbase INTERFACE ${CMAKE_SOURCE_DIR}/deps/bandit ${CMAKE_SOURCE_DIR}/src)

add_subdirectory(dsm)
