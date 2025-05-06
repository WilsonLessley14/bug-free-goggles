cmake_minimum_required(VERSION 3.10)

project(GraphicsJourney VERSION 1.0)

# TODO 7: Set the project version number as 1.0 in the above project command

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
# TODO 8: Use configure_file to configure and copy TutorialConfig.h.in to
#         TutorialConfig.h
configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(tutorial tutorial.cxx)
add_executable(math math_lib/main.cpp math_lib/matrix.cpp math_lib/vector_methods.cpp)
add_executable(sandbox sandbox_lib/sandbox.cpp sandbox_lib/eagerness.cpp)

# TODO 9: Use target_include_directories to include ${PROJECT_BINARY_DIR}
target_include_directories(tutorial PUBLIC
  "${PROJECT_BINARY_DIR}"
)
