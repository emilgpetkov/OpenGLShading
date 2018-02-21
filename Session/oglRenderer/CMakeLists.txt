# Set the name of the project and target:
SET(TARGET "oglRenderer")
#Declare all source files the target consists of:
SET(TARGET_SRC

    oglRenderer_Global.h

oglrenderer.cpp
oglrenderer.h

#You can specify additional files here!
)

cmake_minimum_required( VERSION 3.1 )
project( ${TARGET} )

set(CMAKE_CXX_COMPILER "/usr/bin/g++-4.8")
set(CMAKE_C_COMPILER "/usr/bin/gcc-4.8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Release")

if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	set(BUILD_TARGET "${TARGET}d")
elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
	set(BUILD_TARGET "${TARGET}")
else()
	message(FATAL_ERROR "Invalid build type!")
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC 1)

set(OGLUTILS_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../oglUtils/")
set(OGLUTILS_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglUtils/Release/liboglUtils.so")
set(OGLUTILS_LIBRARIES_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglUtils/Debug/liboglUtilsd.so")

set(OGLGEOMETRY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../oglGeometry/")
set(OGLGEOMETRY_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglGeometry/Release/liboglGeometry.so")
set(OGLGEOMETRY_LIBRARIES_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglGeometry/Debug/liboglGeometryd.so")

set(OGLSHADER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../oglShader/")
set(OGLSHADER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglShader/Release/liboglShader.so")
set(OGLSHADER_LIBRARIES_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglShader/Debug/liboglShaderd.so")

get_property(cxx_features GLOBAL PROPERTY CMAKE_CXX_KNOWN_FEATURES)
set(CMAKE_CXX_COMPILE_FEATURES ${cxx_features})
set(GLOBAL PROPERTY CMAKE_C_COMPILE_FEATURES ${cxx_features})

include_directories(
    ${OGLUTILS_INCLUDE_DIRS}
    ${OGLGEOMETRY_INCLUDE_DIRS}
    ${OGLSHADER_INCLUDE_DIRS}
    )

add_library(${BUILD_TARGET} SHARED ${TARGET_SRC})
target_link_libraries(${BUILD_TARGET} #Qt5::Widgets Qt5::Core Qt5::Gui Qt5::OpenGL
# Add some additional libs
${OGLUTILS_LIBRARIES_DEBUG}
${OGLGEOMETRY_LIBRARIES_DEBUG}
${OGLSHADER_LIBRARIES_DEBUG}
)
