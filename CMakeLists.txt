cmake_minimum_required(VERSION 3.23.3)

# Set CMP0048 to NEW to allow the VERSION argument in the project() command
if(POLICY CMP0048)
    cmake_policy(SET CMP0048 NEW)
endif()

project(FeralAscent
    VERSION 1.0.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#### Setup Directories ####

# Main output directory for the binaries
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####

# SFML dependencies
set(SFML_INCLUDE_DIR "${CMAKE_BINARY_DIR}/../lib/sfml/include")
set(SFML_LIBRARY_DIR "${CMAKE_BINARY_DIR}/../lib/sfml/lib")

# 
set(SFML_LIBRARIES
	sfml-graphics
	sfml-main
	sfml-system
	sfml-network
	sfml-audio
)

# Check if SFML include directory is found
#if(NOT EXISTS ${SFML_INCLUDE_DIR})
#    message(FATAL_ERROR "SFML_INCLUDE_DIR not found: ${SFML_INCLUDE_DIR}")
#else()
#    message(STATUS "SFML_INCLUDE_DIR found: ${SFML_INCLUDE_DIR}")
#    include_directories(${SFML_INCLUDE_DIR})  # Add include directory
#endif()

# Check if SFML library directory is found
#if(NOT EXISTS ${SFML_LIBRARY_DIR})
#    message(FATAL_ERROR "SFML_LIBRARY_DIR not found: ${SFML_LIBRARY_DIR}")
#else()
#    message(STATUS "SFML_LIBRARY_DIR found: ${SFML_LIBRARY_DIR}")
#    link_directories(${SFML_LIBRARIES})  # Add link directory
#endif()


# Include custom library (if applicable)
add_subdirectory(blah/src)

# Add executable
add_executable(FeralAscent ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

# Check if SFML_LIBRARY_DIR is defined and link libraries
#if(SFML_LIBRARY_DIR)
#    message(STATUS "Linking libraries to FeralAscent from: ${SFML_LIBRARY_DIR} to ${OUTPUT_DIRECTORY}")
#    target_link_libraries(FeralAscent PUBLIC blah ${SFML_LIBRARIES})  # Use SFML_LIBRARIES instead
#else()
#    message(WARNING "SFML_LIBRARY_DIR is not defined. Cannot link SFML_LIBRARIES.")
#endif()

# Copy SFML DLLs to the executable's output directory after the build
#foreach(SFML_LIB ${SFML_LIBRARIES})
#    get_filename_component(SFML_DLL_NAME ${SFML_LIB} NAME)
#    add_custom_command(TARGET FeralAscent POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E echo "Copying ${SFML_DLL_NAME}.dll"
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            "${SFML_LIBRARY_DIR}/${SFML_DLL_NAME}-2.dll"
#            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${SFML_DLL_NAME}-2.dll"
#       COMMAND ${CMAKE_COMMAND} -E echo "Copy completed"
#        COMMENT "Copying SFML DLLs to output directory"
#    )
#endforeach()











