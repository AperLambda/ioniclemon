cmake_minimum_required(VERSION 3.6)
project(ioniclemon)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(GenerateExportHeader)
include(utils/CompileUtility)

set(CMAKE_CXX_STANDARD 17)

# Options
#option(IONICLEMON_BUILD_STATIC "Build static libraries" OFF)
option(IONICLEMON_INSTALL "Generate installation target" ON)
option(IONICLEMON_BUILD_EXAMPLES "Build the ioniclemon example programs" ON)
if (LINUX)
    option(IONICLEMON_USE_WAYLAND "Use wayland instead of X11" OFF)
endif ()

generate_flags(IONICLEMON_COMPILE_FLAGS "native" 2 true)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}${IONICLEMON_COMPILE_FLAGS}")

find_package(lambdacommon REQUIRED)
# For the moment it is required as we don't support other platforms yet.
find_package(GLFW REQUIRED)
if (LINUX)
    set(IONICLEMON_ADDITIONAL_LIBRARIES)
    if (NOT IONICLEMON_USE_WAYLAND)
        find_package(X11 REQUIRED)
        list(APPEND IONICLEMON_ADDITIONAL_LIBRARIES "-lGLX ${X11_X11_LIB}")
        set(SOURCE_INTERNAL_X11 src/internal/context_x11.h src/internal/context_x11.cpp)
        add_compile_definitions(IONICLEMON_USE_X11)
    else ()
        find_package(Wayland REQUIRED Client Cursor Egl)
        list(APPEND IONICLEMON_ADDITIONAL_LIBRARIES "${Wayland_LIBRARIES}")
        set(SOURCE_INTERNAL_WL)
    endif ()
endif ()

include_directories(${LAMBDACOMMON_INCLUDE_DIRS} ${X11_INCLUDE_DIR} ${Wayland_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})

# All files:
# There is the C++ header files.
set(HEADER_FILES include/ionic/lemon/ioniclemon.h include/ionic/lemon/window.h)
# There is the C++ source files.
set(SOURCE_INTERNAL ${SOURCE_INTERNAL_X11} ${SOURCE_INTERNAL_WL})
set(SOURCE_WINDOW src/window/window.cpp src/window/window_impl.h src/window/window_null.h src/window/window_x11.h)
set(SOURCE_FILES ${SOURCE_INTERNAL} ${SOURCE_WINDOW} src/ioniclemon.cpp src/context.h)

# Now build the library.
add_library(ioniclemon ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(ioniclemon AperLambda::lambdacommon GLFW::GLFW ${IONICLEMON_ADDITIONAL_LIBRARIES})
set_target_properties(ioniclemon PROPERTIES
                        POSITION_INDEPENDENT_COSE ON)

if (IONICLEMON_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()