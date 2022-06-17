cmake_minimum_required(VERSION 3.7)

project(JS-Engine VERSION 1.0) 

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/") 

find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
# find_package(assimp REQUIRED HINTS ${ASSIMP_DIR}) 

add_definitions(
  -DGLEW_STATIC
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

# Core
file(GLOB CORE_SOURCE  jse/core/*.cpp)
file(GLOB CORE_INCLUDE jse/core/*.hpp)
# Sys
file(GLOB SYS_SOURCE  jse/core/sys/*.cpp)
file(GLOB SYS_INCLUDE jse/core/sys/*.hpp)
# IO
file(GLOB IO_SOURCE  jse/core/io/*.cpp)
file(GLOB IO_INCLUDE jse/core/io/*.hpp)
# Math
file(GLOB MATH_SOURCE  jse/core/math/*.cpp)
file(GLOB MATH_INCLUDE jse/core/math/*.hpp)

# Graphics
file(GLOB GRAPHICS_SOURCE  jse/graphics/*.cpp)
file(GLOB GRAPHICS_INCLUDE jse/graphics/*.hpp)
# Scene
file(GLOB SCENE_SOURCE  jse/scene/*.cpp)
file(GLOB SCENE_INCLUDE jse/scene/*.hpp)
# Input
file(GLOB INPUT_SOURCE  jse/input/*.cpp)
file(GLOB INPUT_INCLUDE jse/input/*.hpp)


file(GLOB SOIL2_INCLUDE external/soil2/incs/*.h)
file(GLOB SOIL2_SOURCE external/soil2/srcs/*.c)


add_library(engine STATIC 
  ${CORE_SOURCE}
  ${CORE_INCLUDE}
  ${IO_SOURCE}
  ${IO_INCLUDE}
  ${SYS_SOURCE}
  ${SYS_INCLUDE}
  ${INPUT_SOURCE}
  ${INPUT_INCLUDE}
  ${GRAPHICS_SOURCE}
  ${GRAPHICS_INCLUDE}
  ${MATH_SOURCE}
  ${MATH_INCLUDE}
  ${SCENE_SOURCE}
  ${SCENE_INCLUDE}
)

add_library(SOIL2 STATIC
  ${SOIL2_INCLUDE}
  ${SOIL2_SOURCE}
)

add_library(glew STATIC
  external/glew-2.1.0/src/glew.c
  external/glew-2.1.0/include/GL/glew.h
)

add_library(stb_image STATIC
  external/stb/stb_image.h
  external/stb/stb_image.c
)

add_library(tinygltf STATIC
  external/tinygltf/tiny_gltf.h
  external/tinygltf/tiny_gltf.cpp
)

include_directories(
  jse/
  external/glew-2.1.0/include/
  external/glm/
  external/stb/
  external/soil2/incs/
  external/tinygltf/
  ${SDL2_INCLUDE_DIR}
)

link_directories(
#  ${ASSIMP_LIBRARY_DIRS}
)

#message(STATUS "Assimp lib path: ${ASSIMP_LIBRARY_DIRS}")

file(GLOB SHADERS assets/shaders/*.glsl)

add_executable(demo	
  demo/demo.cpp
  demo/demo.hpp
  ${SHADERS}  
)

target_link_libraries(demo
  engine
  glew
  stb_image
  tinygltf
  ${OPENGL_LIBRARY}
  ${SDL2_LIBRARIES}
)

if(WIN32)

  if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCH "x64")
  else()
    set(ARCH "x86")
  endif()

#  add_custom_command(TARGET demo POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy
#     "${assimp_DIR}/../../../bin/assimp${ASSIMP_LIBRARY_SUFFIX}.dll"
#     $<TARGET_FILE_DIR:demo>)

  add_custom_command(TARGET demo POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy
     "${SDL2_INCLUDE_DIR}/../lib/${ARCH}/SDL2.dll"
     $<TARGET_FILE_DIR:demo>)
endif()

source_group("Core" FILES ${CORE_SOURCE} ${CORE_INCLUDE})
source_group("Core\\Math" FILES ${MATH_SOURCE} ${MATH_INCLUDE})
source_group("Core\\Sys" FILES ${SYS_SOURCE} ${SYS_INCLUDE})
source_group("Core\\Io" FILES ${IO_SOURCE} ${IO_INCLUDE})
source_group("Graphics" FILES ${GRAPHICS_SOURCE} ${GRAPHICS_INCLUDE})
source_group("Scene" FILES ${SCENE_SOURCE} ${SCENE_INCLUDE})
source_group("Input" FILES ${INPUT_SOURCE} ${INPUT_INCLUDE})
