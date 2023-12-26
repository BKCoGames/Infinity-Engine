cmake_minimum_required(VERSION 3.27)
project(Test_Renderer)

set(CMAKE_CXX_STANDARD 20)

##################
##### Lists ######
##################

# Source files
set(SOURCE_FILES src/main.cpp
        src/engine/core/io/IOManager.cpp
        src/engine/core/InfEngine.cpp
        src/engine/renderer/IERenderer.cpp
        src/engine/core/log/LogManager.cpp
)

# Private include directories
set(PRIVATE_INCLUDE_DIRECTORIES src/engine)

# Public include directories
set(PUBLIC_INCLUDE_DIRECTORIES)

# Target link directories (private)
set(PRIVATE_TARGET_LINK_DIRECTORIES)

# Target link directories (public)
set(PUBLIC_TARGET_LINK_DIRECTORIES)

# Target link libraries
set(TARGET_LINK_LIBRARIES)

# Global includes
set(GLOBAL_HEADERS)


##################
##### Lists ######
##################

# Build specific global macro headers
set(GLOBAL_MACROS ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/build_macros/Default_Build_Macros.h)

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
# list(APPEND TARGET_LINK_LIBRARIES glfw)

# Linking SDL
add_subdirectory(ThirdPartyLibs/SDL-release-2.28.5)
find_package(SDL2 CONFIG REQUIRED)
list(APPEND PRIVATE_INCLUDE_DIRECTORIES ${SDL2_INCLUDE_DIRS})
list(APPEND TARGET_LINK_LIBRARIES SDL2::SDL2main SDL2::SDL2-static)

# Linking GLAD
list(APPEND SOURCE_FILES ThirdPartyLibs/GLAD/src/glad.c)
list(APPEND PUBLIC_INCLUDE_DIRECTORIES ThirdPartyLibs/GLAD/headers)

# Linking opengl
find_package(OpenGL REQUIRED)
list(APPEND TARGET_LINK_LIBRARIES ${OPENGL_LIBRARIES})

# Linking boost library
find_package(Boost 1.81.0 REQUIRED COMPONENTS filesystem)
list(APPEND TARGET_LINK_LIBRARIES ${Boost_LIBRARIES})
list(APPEND PRIVATE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})

###############################
##### External Libraries ######
###############################

###############################
#####   Build Settings   ######
###############################

# Build macros
if (DEBUG_BUILD)
    list(APPEND GLOBAL_MACROS ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/build_macros/Debug_Build_Macros.h)
    add_definitions(-g)
elseif (RELEASE_BUILD)
    list(APPEND GLOBAL_MACROS ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/build_macros/Release_Build_Macros.h)
    add_definitions(-g)
elseif (DEVELOPMENT_BUILD)
    list(APPEND GLOBAL_MACROS ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/build_macros/Development_Build_Macros.h)
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
foreach(GLOBAL_MACRO IN LISTS GLOBAL_MACROS)
    # Include each file in order
    add_definitions(-include ${GLOBAL_MACRO})
endforeach()

#include global headers
foreach(GLOBAL_HEADER IN LISTS GLOBAL_HEADERS)
    # Include each file in order
    add_definitions(-include ${GLOBAL_HEADER})
endforeach()

# Includes
target_include_directories(Test_Renderer PUBLIC BEFORE ${PUBLIC_INCLUDE_DIRECTORIES})
target_include_directories(Test_Renderer PRIVATE BEFORE ${PRIVATE_INCLUDE_DIRECTORIES})

# Target Linking
target_link_libraries(Test_Renderer ${TARGET_LINK_LIBRARIES})
target_link_directories(Test_Renderer PRIVATE ${PRIVATE_TARGET_LINK_DIRECTORIES})
target_link_directories(Test_Renderer PUBLIC ${PUBLIC_TARGET_LINK_DIRECTORIES})


###############################
#####  Building Project  ######
###############################