include_directories(../include)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

add_executable(ioniclemon_basic_window basic_window.cpp)
target_link_libraries(ioniclemon_basic_window AperLambda::lambdacommon ioniclemon GLEW::GLEW OpenGL::GL)