cmake_minimum_required(VERSION 3.28)

# Set project name and version
project(GameLife LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



# Set option to control setting the resource path variable 
option(USE_INSTALL_RESOURCE_PATH "Set resource path to install location" OFF)

if(NOT USE_INSTALL_RESOURCE_PATH)
    set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/assets")
else()
    set(RESOURCE_PATH "${CMAKE_INSTALL_PREFIX}/share/${CMAKE_PROJECT_NAME}/assets/")
endif()

    

include(FetchContent)

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG v3.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)


# Compile the target source files into an executable call gameLife
add_executable(gameLife)
target_sources(gameLife PRIVATE 
    src/main.cpp 
    src/gameLife.cpp
    src/simulation.cpp 
    )

target_compile_features(gameLife PRIVATE cxx_std_17)
target_compile_options(gameLife PRIVATE -Wall -Wextra -pedantic)

# set include directory search paths
target_include_directories(gameLife 
    PRIVATE 
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

# Link executable to required SFML modules
target_link_libraries(gameLife PRIVATE SFML::Graphics)
