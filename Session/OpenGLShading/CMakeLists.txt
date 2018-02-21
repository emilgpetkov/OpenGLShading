# Set the name of the project and target:
SET(TARGET "OpenGLShading")
#Declare all source files the target consists of:
SET(TARGET_SRC

main.cpp
#You can specify additional files here!
)

cmake_minimum_required( VERSION 3.1 )
project( ${TARGET} )

set(CMAKE_CXX_COMPILER "/usr/bin/g++-4.8")
set(CMAKE_C_COMPILER "/usr/bin/gcc-4.8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE "Release")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC 1)

# Find the QtWidgets library
set(QT_QMAKE_EXECUTABLE "/opt/Qt/5.10.0/gcc_64/bin/qmake")
find_package(Qt5Widgets)
find_package(Qt5 REQUIRED COMPONENTS Core Gui OpenGL)

include_directories(/windows/Dev-Cpp/Projects/OpenGLShading/Session/oglGUI
)

set(OGLUTILS_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../oglUtils/")
set(OGLUTILS_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglUtils/Release/liboglUtils.so")
set(OGLUTILS_LIBRARIES_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglUtils/Debug/liboglUtilsd.so")

set(OGLSHADER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../oglShader/")
set(OGLSHADER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglShader/Release/liboglShader.so")
set(OGLSHADER_LIBRARIES_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglShader/Debug/liboglShaderd.so")

set(OGLGEOMETRY_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../oglGeometry/")
set(OGLGEOMETRY_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglGeometry/Release/liboglGeometry.so")
set(OGLGEOMETRY_LIBRARIES_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglGeometry/Debug/liboglGeometryd.so")

set(OGLRENDERER_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../oglRenderer/")
set(OGLRENDERER_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglRenderer/Release/liboglRenderer.so")
set(OGLRENDERER_LIBRARIES_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglRenderer/Debug/liboglRendererd.so")

set(OGLGUI_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../oglGUI/")
set(OGLGUI_LIBRARIES "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglGUI/Release/liboglgui.so")
set(OGLGUI_LIBRARIES_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/../../Build/Linux/oglGUI/Debug/liboglGUId.so")

get_property(cxx_features GLOBAL PROPERTY CMAKE_CXX_KNOWN_FEATURES)
set(CMAKE_CXX_COMPILE_FEATURES ${cxx_features})
set(GLOBAL PROPERTY CMAKE_C_COMPILE_FEATURES ${cxx_features})

include_directories(
    ${OGLGUI_INCLUDE_DIRS}
    ${OGLUTILS_INCLUDE_DIRS}
    ${OGLSHADER_INCLUDE_DIRS}
    ${OGLGEOMETRY_INCLUDE_DIRS}
    ${OGLRENDERER_INCLUDE_DIRS}
    )

add_executable( ${TARGET} ${TARGET_SRC} main.cpp)
target_link_libraries(${TARGET} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::OpenGL
# Add some additional libs
${OGLGEOMETRY_LIBRARIES_DEBUG}
${OGLUTILS_LIBRARIES_DEBUG}
${OGLSHADER_LIBRARIES_DEBUG}
${OGLRENDERER_LIBRARIES_DEBUG}
${OGLGUI_LIBRARIES_DEBUG}
)
