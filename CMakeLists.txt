cmake_minimum_required(VERSION 3.10)
project(ASCII3DRenderer VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Source files
set(CORE_SOURCES
    core/renderer.cpp
)

set(LOG_SOURCES
    log/logger.cpp
)

set(UI_SOURCES
    ui/ui.cpp
)

set(MAIN_SOURCES
    main.cpp
)

# Create the main executable
add_executable(ascii3d 
    ${MAIN_SOURCES}
    ${CORE_SOURCES}
    ${LOG_SOURCES}
    ${UI_SOURCES}
)

# Link libraries
if(UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(ascii3d Threads::Threads)
endif()

# Create log directory during build
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/log)

# Installation
install(TARGETS ascii3d DESTINATION bin)

# Create example executable with original donut
add_executable(original_donut donut.cpp)

# Package configuration
set(CPACK_PACKAGE_NAME "ASCII3DRenderer")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ASCII 3D Shape Renderer")
set(CPACK_PACKAGE_VENDOR "ASCII3D Project")

include(CPack)