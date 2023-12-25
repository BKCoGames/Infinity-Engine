cmake_minimum_required(VERSION 3.27)
project(Test_Renderer)

set(CMAKE_CXX_STANDARD 20)

##################
##### Lists ######
##################

# Source files
set(SOURCE_FILES src/main.cpp)
# Private include directories
set(PRIVATE_INCLUDE_DIRECTORIES)
# Public include directories
set(PUBLIC_INCLUDE_DIRECTORIES)
# Target links
set(TARGET_LINKS)

list(APPEND SOURCE_FILES src/engine/core/InfEngine.cpp)
list(APPEND SOURCE_FILES src/engine/renderer/IERenderer.cpp)
list(APPEND PRIVATE_INCLUDE_DIRECTORIES src/engine)


##################
##### Lists ######
##################

# Build specific global macro headers
set(BUILD_MACRO_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/build_macros/Default_Build_Macros.h)

# Build options
option(RELEASE_BUILD "release build" OFF)
option(DEVELOPMENT_BUILD "development build" OFF)
option(DEBUG_BUILD "debug build" OFF)

###############################
##### External Libraries ######
###############################

# Linking GLFW
# add_subdirectory(ThirdPartyLibs/GLFW/glfw-3.3.9)
# list(APPEND PRIVATE_INCLUDE_DIRECTORIES ThirdPartyLibs/GLFW/Headers)
# list(APPEND TARGET_LINKS glfw)

# Linking SDL
add_subdirectory(ThirdPartyLibs/SDL-release-2.28.5)
list(APPEND PRIVATE_INCLUDE_DIRECTORIES ThirdPartyLibs/SDL-release-2.28.5/include)
list(APPEND TARGET_LINKS SDL2main SDL2-static)

# Linking GLAD
list(APPEND SOURCE_FILES ThirdPartyLibs/GLAD/src/glad.c)
list(APPEND PUBLIC_INCLUDE_DIRECTORIES ThirdPartyLibs/GLAD/headers)

# Linking opengl
find_package(OpenGL REQUIRED)
list(APPEND TARGET_LINKS ${OPENGL_LIBRARIES})

# Linking boost library
list(APPEND PRIVATE_INCLUDE_DIRECTORIES ThirdPartyLibs/boost_1_84_0)

###############################
##### External Libraries ######
###############################

###############################
#####   Build Settings   ######
###############################

# Build macros
if (DEBUG_BUILD)
    list(APPEND BUILD_MACRO_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/build_macros/Debug_Build_Macros.h)
    add_definitions(-g)
elseif (RELEASE_BUILD)
    list(APPEND BUILD_MACRO_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/build_macros/Release_Build_Macros.h)
    add_definitions(-g)
elseif (DEVELOPMENT_BUILD)
    list(APPEND BUILD_MACRO_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/build_macros/Development_Build_Macros.h)
endif ()

###############################
#####   Build Settings   ######
###############################


###############################
#####  Building Project  ######
###############################


# Executable
add_executable(Test_Renderer ${SOURCE_FILES})

#include global build macros
foreach(BUILD_MACRO_HEADER IN LISTS BUILD_MACRO_HEADERS)
    # Include each file in order
    add_definitions(-include ${BUILD_MACRO_HEADER})
endforeach()

# TODO delete this later. for testing
list(APPEND PRIVATE_INCLUDE_DIRECTORIES src/Temp)

# Includes
target_include_directories(Test_Renderer PUBLIC BEFORE ${PUBLIC_INCLUDE_DIRECTORIES})
target_include_directories(Test_Renderer PRIVATE BEFORE ${PRIVATE_INCLUDE_DIRECTORIES})

# Target Linking
target_link_libraries(Test_Renderer ${TARGET_LINKS})

###############################
#####  Building Project  ######
###############################