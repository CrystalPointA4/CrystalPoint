cmake_minimum_required(VERSION 3.5)
project(CrystalPoint)

file(GLOB SOURCE_FILES
        "*.h"
        "*.cpp"
        )

add_executable(CrystalPoint ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(CrystalPoint ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall ")
