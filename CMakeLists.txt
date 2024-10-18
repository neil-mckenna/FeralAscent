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



# create a recursive header and cpp include
#file(GLOB_RECURSE SRC_FILES src/*.cpp)
# creates a executable with the following name
#add_executable(FeralAscent ${CMAKE_CURRENT_SOURCE_DIR}/FeralAscent/src/main.cpp ${SRC_FILES})

# create a link to header files
#target_include_directories(FeralAscent PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


# add a static library, only cpp files
#add_library(blah STATIC blah/src/Blah.cpp)
#target_include_directories(blah PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/blah/src)

# point to another library with a cmake inside
#find_package(SFML 2 REQUIRED network audio graphics window system)


# Project start here


# this was test for a custom file Blah Class
add_subdirectory(blah/src)
# add executable, Project name, main.cpp or exe 
add_executable(FeralAscent ${CMAKE_CURRENT_SOURCE_DIR}/FeralAscent/src/main.cpp)
# target libaries, link project to the static libaries
target_link_libraries(FeralAscent PUBLIC blah)
#target_link_directories(FeralAscent PUBLIC blah ${blah} ${SFML_DEPENDENCIES})












