cmake_minimum_required(VERSION 3.5)
project(CrystalPoint)

file(GLOB_RECURSE SOURCE_FILES
        "*.h"
        "*.cpp"
        "*.cc"
        )

add_executable(CrystalPoint ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenAL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${OPENAL_INCLUDE_DIRS} )
target_link_libraries(CrystalPoint ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${OPENAL_LIBRARY} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -lpthread")