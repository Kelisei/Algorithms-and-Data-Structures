cmake_minimum_required(VERSION 3.10)

# Set the project name
project(AlgorithmsAndDataStructures)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files
set(SOURCES
    testing/main.cpp
    testing/linked_list_test.cpp
    libraries/minitest.cpp
)

# Add the header files
set(HEADERS
    libraries/minitest.hpp
    libraries/minitest.tpp
    data_structures/linked_list.hpp
    data_structures/linked_list.tpp
)

# Add the executable
add_executable(AlgorithmsAndDataStructures ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(AlgorithmsAndDataStructures PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libraries
    ${CMAKE_CURRENT_SOURCE_DIR}/data_structures
    ${CMAKE_CURRENT_SOURCE_DIR}/testing
)