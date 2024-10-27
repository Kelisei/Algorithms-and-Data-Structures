cmake_minimum_required(VERSION 3.10)
project(AaDS)

# Add source files
set(SOURCE_FILES 
    algorithms/algorithms.cpp
    data_structures/linked_list.tpp
    data_structures/avl_tree.tpp
)

# Add the GoogleTest framework
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add the libraries
add_library(algorithms ${SOURCE_FILES})
add_library(data_structures ${SOURCE_FILES})

# Add the test executable
add_executable(
    algorithms_test
    algorithms/algorithms_test.cpp
    tests/main_test.cpp
    data_structures/linked_list_test.cpp
    data_structures/avl_tree_test.cpp  # Add the avl_tree test file
)

# Link libraries to the test executable
target_link_libraries(
    algorithms_test
    algorithms
    data_structures
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(algorithms_test)