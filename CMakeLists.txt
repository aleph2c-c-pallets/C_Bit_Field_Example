cmake_minimum_required(VERSION 3.10)

# Set the project name
project (C_bit_field)

# Glob the source files
file(GLOB SOURCES "src/*.c")

file(GLOB TESTS "test/*.c")

# Main executable
add_executable(bitfield main.c ${SOURCES})

target_include_directories( bitfield PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
)

# Test executable
enable_testing()
add_executable(tests ${SOURCES} ${TESTS})
target_include_directories( tests PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/inc"
    "${PROJECT_SOURCE_DIR}/test"
)
target_link_libraries(tests cmocka)
add_test(NAME bitfield_tests COMMAND tests)