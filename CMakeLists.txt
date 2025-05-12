cmake_minimum_required(VERSION 3.10)

project(GraphicsJourney VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO 2: Use add_subdirectory() to add math_lib to this project

add_executable(tutorial tutorial.cxx)
add_executable(sandbox sandbox_lib/sandbox.cpp sandbox_lib/eagerness.cpp)

# TODO 3: Use target_link_libraries to link the library to our executable

# TODO 4: Add math_lib to Tutorial's target_include_directories()
# Hint: ${PROJECT_SOURCE_DIR} is a path to the project source. AKA This folder!

target_include_directories(tutorial PUBLIC
  "${PROJECT_BINARY_DIR}"
)
