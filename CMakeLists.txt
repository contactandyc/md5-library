cmake_minimum_required(VERSION 3.10)
project(md5library VERSION 0.1.1)

# Options
option(DEBUG "Enable debugging" OFF)
option(ADDRESS_SANITIZER "Enable Address Sanitizer" OFF)

set(CMAKE_INSTALL_INCLUDEDIR include)
set(CMAKE_INSTALL_BINDIR bin)
set(CMAKE_INSTALL_DOCDIR share/doc/md5library)
set(CMAKE_C_STANDARD 99)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Compiler options
if(ADDRESS_SANITIZER)
    add_compile_options(-fsanitize=address)
endif()

# Source files
set(SOURCE_FILES src/md5.c)

# Debug library
add_library(md5library_debug STATIC ${SOURCE_FILES})
target_include_directories(md5library_debug PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_options(md5library_debug PRIVATE -g -O0)
set_target_properties(md5library_debug PROPERTIES OUTPUT_NAME "md5library_debug")
target_compile_options(md5library_debug PRIVATE -g -O0)


# Release library
add_library(md5library_static STATIC ${SOURCE_FILES})
target_include_directories(md5library_static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_options(md5library_static PRIVATE -O3)
set_target_properties(md5library_static PROPERTIES OUTPUT_NAME "md5library_static")
target_compile_options(md5library_static PRIVATE -O3)

# Shared library
add_library(md5library SHARED ${SOURCE_FILES})
target_include_directories(md5library PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
target_compile_options(md5library PRIVATE -O3)
set_target_properties(md5library PROPERTIES OUTPUT_NAME "md5library")
target_compile_options(md5library PRIVATE -O3)

# Installation of the library
install(TARGETS md5library md5library_static md5library_debug
        EXPORT md5libraryTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include)

# Export the targets
install(EXPORT md5libraryTargets
        FILE md5libraryTargets.cmake
        DESTINATION lib/cmake/md5library)

# Create and install the config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "md5libraryConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

configure_file(md5libraryConfig.cmake.in md5libraryConfig.cmake @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/md5libraryConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/md5libraryConfigVersion.cmake"
        DESTINATION lib/cmake/md5library)

# Installation of other files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/md5-library DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES README.md AUTHORS NEWS.md CHANGELOG.md LICENSE NOTICE DESTINATION ${CMAKE_INSTALL_DOCDIR})

# Uninstall command
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/bin/cmake_uninstall.cmake.in"
               "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
               IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
