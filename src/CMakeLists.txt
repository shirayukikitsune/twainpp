add_library(twain++ error_code.h error_condition.h twain++.h)

target_sources(twain++ PRIVATE error_code.cpp error_condition.cpp external/twain.h)

# In OSX, TWAIN library is a framework that must be statically linked
if (APPLE)
    find_library(TWAIN_LIBRARY TWAIN)
    mark_as_advanced(TWAIN_LIBRARY)
    target_link_libraries(twain++ LINK_INTERFACE_LIBRARIES ${TWAIN_LIBRARY})
endif()

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.16.0")
    target_precompile_headers(twain++ PUBLIC precompiled.h)
else()
    target_sources(twain++ PRIVATE precompiled.h)
endif()

set_target_properties(twain++
    PROPERTIES
        FRAMEWORK ON
        SOVERSION 0
        VERSION 0.1
        ARCHIVE_OUTPUT_DIRECTORY "lib"
        LIBRARY_OUTPUT_DIRECTORY "lib"
        OUTPUT_NAME kitsune-twain++
)

install(TARGETS twain++
        FRAMEWORK DESTINATION lib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)

install(DIRECTORY . DESTINATION include/kitsune/twain++
        FILES_MATCHING PATTERN "*.h")
