cmake_minimum_required(VERSION 3.16)
project(cngui VERSION 1.0 LANGUAGES CXX)

include(FetchContent)

# ----------------------------
# Options
# ----------------------------
option(CNGUI_SHARED_LIBS "Build shared library" OFF)
option(CNGUI_STATIC_STD_LIBS "Use static runtime (only applies to MSVC/GCC)" OFF)

# ----------------------------
# Build Type Default
# ----------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose build type: Debug or Release" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ----------------------------
# Fetch SFML 2.6.2
# ----------------------------
if(NOT CNGUI_SHARED_LIBS)
  set(SFML_STATIC_LIBRARIES TRUE)
endif()

FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(sfml)

# ----------------------------
# Find OpenGL
# ----------------------------
find_package(OpenGL REQUIRED)

# ----------------------------
# Source Setup
# ----------------------------
set(CNGUI_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(CNGUI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE CNGUI_HEADERS CONFIGURE_DEPENDS
  ${CNGUI_INCLUDE_DIR}/CNGui/*.hpp
)

file(GLOB_RECURSE CNGUI_SOURCES CONFIGURE_DEPENDS
  ${CNGUI_SOURCE_DIR}/CNGui/*.cpp
)

# ----------------------------
# Target Definition
# ----------------------------
if(CNGUI_SHARED_LIBS)
  add_library(cngui SHARED ${CNGUI_HEADERS} ${CNGUI_SOURCES})
else()
  add_library(cngui STATIC ${CNGUI_HEADERS} ${CNGUI_SOURCES})
endif()

add_library(cngui::cngui ALIAS cngui)

# ----------------------------
# Target Settings
# ----------------------------
target_include_directories(cngui
  PUBLIC ${CNGUI_INCLUDE_DIR}
)

target_link_libraries(cngui
  PUBLIC
    sfml-graphics
    sfml-main
    OpenGL::GL
)

if(CNGUI_STATIC_STD_LIBS AND MSVC)
  foreach(flag_var
    CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
    string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
  endforeach()
elseif(CNGUI_STATIC_STD_LIBS AND CMAKE_COMPILER_IS_GNUCXX)
  target_compile_options(cngui PRIVATE -static-libgcc -static-libstdc++)
endif()

set_target_properties(cngui PROPERTIES
  POSITION_INDEPENDENT_CODE ON
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN ON
)

# ----------------------------
# Install (optional)
# ----------------------------
# install(TARGETS cngui EXPORT cnguiTargets DESTINATION lib)
# install(DIRECTORY ${CNGUI_INCLUDE_DIR}/ DESTINATION include)

