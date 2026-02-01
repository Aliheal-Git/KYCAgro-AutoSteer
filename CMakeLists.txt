cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Set the following variable to `ON` to print all cmake variables


# Set the project name
set(CMAKE_PROJECT_NAME KYC)

# Enable CMake support for ASM C CXX languages
enable_language(C CXX ASM)

# Set the following variable to `ON` to print all cmake variables
set(CMAKE_DUMP_VARIABLES            OFF)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(NOTICE "Build type: ${CMAKE_BUILD_TYPE}")

# Get the number of processors available
include(ProcessorCount)
ProcessorCount(NPROC)

# Include the required build tools
# include(cmake/tools/clang-tools.cmake)
# include(cmake/tools/python.cmake)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Recursively find all C and C++ files
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/app/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/app/*.cc"
)

# Print each found file
message(STATUS "Found source files:")
foreach(FILE_PATH IN LISTS SOURCES)
    message(STATUS "  ${FILE_PATH}")
endforeach()

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${SOURCES}
)

# Set include paths
set(INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Drivers/Button
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Drivers/Flash
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Drivers/Flowmeter
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Drivers/GPS
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Drivers/LCDScreen
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Drivers/Micros
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Drivers/Valve
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Drivers/Window
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Controller/DosageController
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Controller/ValveController
    ${CMAKE_CURRENT_SOURCE_DIR}/App/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Page
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Services
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Domain
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${INCLUDES}
)

# Set defines
set(DEFINES
    STM32H735XX
    USE_HAL_DRIVER
    USE_FULL_ASSERT
    $<IF:$<CONFIG:Debug>,DEBUG,NDEBUG>
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
    ${DEFINES}
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)


# Generate size information
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
)

# Generate binary output
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
    COMMAND ${CMAKE_COMMAND} -E echo "Bin output created: ${TARGET_BIN_OUTPUT}"
)

# Generate hex output
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_COMMAND} -E echo "Hex output created: ${TARGET_HEX_OUTPUT}"
)

# # Add custom target to check source code formatting with clang-format
# add_custom_target(check-format
#     COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/script/clang_format.py
#             --check
#             --style=file
#             --executable=${CLANG_FORMAT}
#             ${INCLUDES} ${SOURCES}
#     COMMENT "Check source code formatting..."
# )

# # Add custom target to run clang-format
# add_custom_target(run-format
#     COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/script/clang_format.py
#             --style=file
#             --executable=${CLANG_FORMAT}
#             ${INCLUDES} ${SOURCES}
#     COMMENT "Run source code formatting..."
# )

# # Add custom target to run clang-tidy
# set(CLANG_TIDY_DEFINES
#     ${DEFINES}
# )
# set(CLANG_TIDY_INCLUDES
#     ${INCLUDES}
# )
# list(TRANSFORM CLANG_TIDY_DEFINES PREPEND -D)
# list(TRANSFORM CLANG_TIDY_INCLUDES PREPEND -I)
# list(TRANSFORM CLANG_TIDY_SYSTEM_INCLUDES PREPEND -isystem)
# add_custom_target(tidy
#     COMMAND ${CLANG_TIDY}
#             ${CLANG_TIDY_ARGS}
#             ${SOURCES}
#             --
#             ${CLANG_TIDY_EXTRA_ARGS}
#             ${CLANG_TIDY_DEFINES}
#             ${CLANG_TIDY_INCLUDES}
#             ${CLANG_TIDY_SYSTEM_INCLUDES}
#     COMMENT "Run clang-tidy..."
# )

# # Create directories for cppcheck because they are not created automatically
# set(CPPCHECK_BUILD_DIR ${CMAKE_BINARY_DIR}/cppcheck)
# set(CPPCHECK_REPORT_DIR ${CMAKE_BINARY_DIR}/cppcheck/report)
# file(MAKE_DIRECTORY ${CPPCHECK_BUILD_DIR})
# file(MAKE_DIRECTORY ${CPPCHECK_REPORT_DIR})

# # Add custom target to run cppcheck
# add_custom_target(cppcheck
#     COMMAND cppcheck
#             --project=${CMAKE_BINARY_DIR}/compile_commands.json
#             --cppcheck-build-dir=${CPPCHECK_BUILD_DIR}
#             --checkers-report=${CPPCHECK_REPORT_DIR}/checkers.txt
#             --addon=${PROJECT_SOURCE_DIR}/lint/misra.json
#             --check-level=exhaustive
#             --enable=all
#             --error-exitcode=1
#             --inconclusive
#             --inline-suppr
#             --max-ctu-depth=10
#             --safety
#             --std=c11
#             --suppressions-list=${PROJECT_SOURCE_DIR}/lint/suppressions.txt
#             -D__GNUC__
#             -j${NPROC}
#     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
#     COMMENT "Running cppcheck..."
# )

# Add custom target to generate doxygen documentation
add_custom_target(doxygen
    COMMAND doxygen docs/doxygen/Doxyfile && make -C build/doxygen/latex
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generate doxygen documentation..."
)

# Specify additional clean files
set_property(TARGET ${CMAKE_PROJECT_NAME} APPEND PROPERTY ADDITIONAL_CLEAN_FILES
    ${CMAKE_PROJECT_NAME}.map
    ${CMAKE_PROJECT_NAME}.bin
    ${CMAKE_PROJECT_NAME}.hex
)

# Dump all cmake variables
if(CMAKE_DUMP_VARIABLES)
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif()