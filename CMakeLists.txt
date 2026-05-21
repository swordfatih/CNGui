cmake_minimum_required(VERSION 3.30)

project(cngui LANGUAGES CXX VERSION 2.0.0)

option(CNGUI_BUILD_EXAMPLES "Build all example executables" OFF)
option(CNGUI_BUILD_TESTS "Build the test executable" OFF)

include(FetchContent)
if(CNGUI_BUILD_TESTS)
    include(CTest)
    enable_testing()
endif()

function(cngui_link_static_runtime target_name)
    if(MINGW)
        target_link_options(${target_name} PRIVATE -static -static-libgcc -static-libstdc++)
    endif()
endfunction()

# ------------------------
# Dependencies
# ------------------------
set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use SFML as static library")
set(SFML_STATIC TRUE)

FetchContent_Declare(sfml GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 3.1.0 GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(sfml)

# ------------------------
# Library
# ------------------------
file(GLOB_RECURSE cpp_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} STATIC)
add_library(cngui::cngui ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE ${cpp_sources})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_26)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
target_compile_options(${PROJECT_NAME} PUBLIC -freflection PRIVATE -Wall -Wextra -Wpedantic -Wno-unused-but-set-variable -Wno-unused-parameter)

# ------------------------
# Examples
# ------------------------
if(CNGUI_BUILD_EXAMPLES)
    FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.x GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(spdlog)

    file(GLOB example_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")

    foreach(example_source IN LISTS example_sources)
        get_filename_component(example_name "${example_source}" NAME_WE)
        set(example_target "${PROJECT_NAME}_${example_name}")

        add_executable(${example_target} "${example_source}")
        set_target_properties(${example_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime")
        target_link_libraries(${example_target} PRIVATE cngui::cngui SFML::Graphics spdlog::spdlog)
        cngui_link_static_runtime(${example_target})
        target_compile_options(${example_target} PRIVATE -Wall -Wextra -Wpedantic -Wno-unused-but-set-variable -Wno-unused-parameter)
    endforeach()
endif()

# ------------------------
# Tests
# ------------------------
if(CNGUI_BUILD_TESTS)
    FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.14.0 GIT_SHALLOW TRUE)
    FetchContent_MakeAvailable(Catch2)

    file(GLOB_RECURSE test_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

    if(test_sources)
        add_executable(${PROJECT_NAME}_tests ${test_sources})
        set_target_properties(${PROJECT_NAME}_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/runtime")
        target_link_libraries(${PROJECT_NAME}_tests PRIVATE cngui::cngui Catch2::Catch2WithMain)
        cngui_link_static_runtime(${PROJECT_NAME}_tests)
        target_compile_options(${PROJECT_NAME}_tests PRIVATE -Wall -Wextra -Wpedantic -Wno-unused-but-set-variable -Wno-unused-parameter)
        include(${catch2_SOURCE_DIR}/extras/Catch.cmake)
        catch_discover_tests(${PROJECT_NAME}_tests)
    endif()
endif()
