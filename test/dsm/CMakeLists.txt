add_executable(test_dsm test.cpp)

target_link_libraries(test_dsm PUBLIC kitsune-twain++-testbase)

add_test(NAME test_dsm COMMAND test_dsm --reporter=spec)
