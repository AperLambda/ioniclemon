cmake_minimum_required(VERSION 3.6)
project(ioniclemon)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(GenerateExportHeader)
include(utils/CompileUtility)

set(CMAKE_CXX_STANDARD 17)

# Options
#option(IONICLEMON_BUILD_STATIC "Build static libraries" OFF)
option(IONICLEMON_INSTALL "Generate installation target" ON)
option(IONICLEMON_BUILD_TESTS "Build the ioniclemon test programs" ON)

generate_flags(IONICLEMON_COMPILE_FLAGS "native" 2 true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}${IONICLEMON_COMPILE_FLAGS}")

# For the moment it is required as we don't support other platforms yet.
find_package(GLFW REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})

# All files:
# There is the C++ header files.
set(HEADER_FILES include/ionic/lemon/ioniclemon.h)
# There is the C++ source files.
set(SOURCE_FILES src/ioniclemon.cpp)

# Now build the library.
add_library(ioniclemon ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(ioniclemon GLFW::GLFW)

