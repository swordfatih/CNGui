cmake_minimum_required(VERSION 3.11)

set(CNGUI_SHARED_LIBS TRUE CACHE BOOL "Build shared libraries (use shared SFML librares)")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(cngui)

set(cngui_VERSION_MAJOR 1)
set(cngui_VERSION_MINOR 0)

if(NOT CNGUI_SHARED_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

set(SFML_DIR "" CACHE PATH "Folder that contains SFMLConfig.cmake (usually in lib/cmake/SFML/)")

if(NOT SFML_DIR)
	message(SEND_ERROR "Please provide path for the folder that contains SFMLConfig.cmake in SFML_DIR (usually SFML/lib/cmake/SFML/)")
endif()

find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS graphics main QUIET)

if(SFML_FOUND)
	message(STATUS "Found SFML in ${SFML_DIR}")
endif()

# Define sources
set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_PATH "${CMAKE_SOURCE_DIR}/src")

include_directories("${INCLUDE_PATH}")
include_directories("${SOURCE_PATH}")

add_library(cngui 
	"${INCLUDE_PATH}/CNGui/CNGui.hpp"
	"${INCLUDE_PATH}/CNGui/Containers/Container.hpp"
	"${INCLUDE_PATH}/CNGui/Objects/Object.hpp"
	"${INCLUDE_PATH}/CNGui/Objects/Button.hpp"
	"${INCLUDE_PATH}/CNGui/Objects/ProgressIndicator.hpp"
	"${INCLUDE_PATH}/CNGui/Objects/LineEdit.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/Text.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/Style.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/Shape.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/EventHandler.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/FunctionWrapper.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/Font.hpp"
	"${SOURCE_PATH}/CNGui/Objects/Object.cpp"
	"${SOURCE_PATH}/CNGui/Objects/LineEdit.cpp"
	"${SOURCE_PATH}/CNGui/Objects/Button.cpp"
	"${SOURCE_PATH}/CNGui/Objects/ProgressIndicator.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/EventHandler.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/FunctionWrapper.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/Text.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/Style.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/Shape.cpp"
)

target_link_libraries(cngui sfml-graphics sfml-main ${OPENGL_gl_LIBRARY})
