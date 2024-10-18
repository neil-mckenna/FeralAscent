# Create a static library called "blah" from the source file Blah.cpp
add_library(blah STATIC Blah.cpp)

# Optionally, specify include directories if your library has headers
#target_include_directories(blah PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(blah PUBLIC ../include)