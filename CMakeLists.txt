cmake_minimum_required(VERSION 3.11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(cngui)

set(cngui_VERSION_MAJOR 1)
set(cngui_VERSION_MINOR 0)

include_directories("${PROJECT_BINARY_DIR}/bin")

# Define sources
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )

set(
	SOURCES
	"${INCLUDE_PATH}/CNGui.hpp"
	"${INCLUDE_PATH}/CNGui/Containers/Container.hpp"
	"${INCLUDE_PATH}/CNGui/Objects/Object.hpp"
	"${INCLUDE_PATH}/CNGui/Objects/Button.hpp"
	"${INCLUDE_PATH}/CNGui/Objects/ProgressIndicator.hpp"
	"${INCLUDE_PATH}/CNGui/Objects/LineEdit.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/Text.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/Style.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/Shape.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/EventHandler.hpp"
	"${INCLUDE_PATH}/CNGui/Utilities/Font.hpp"
	"${SOURCE_PATH}/CNGui/Objects/Object.cpp"
	"${SOURCE_PATH}/CNGui/Objects/LineEdit.cpp"
	"${SOURCE_PATH}/CNGui/Objects/Button.cpp"
	"${SOURCE_PATH}/CNGui/Objects/ProgressIndicator.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/EventHandler.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/Text.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/Style.cpp"
	"${SOURCE_PATH}/CNGui/Utilities/Shape.cpp"
)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/cmake")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(${EXECUTABLE_NAME} $(SOURCES))

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(cngui SFML::graphics)
endif()


# Install target
install(TARGETS cngui sfml-graphics sfml-window sfml-system CONFIGURATIONS ${CMAKE_BUILD_TYPE} RUNTIME DESTINATION ${PROJECT_BINARY_DIR})

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${cngui_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${cngui_VERSION_MINOR}")
include(CPack)