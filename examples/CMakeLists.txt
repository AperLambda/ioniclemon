include_directories(../include)

add_executable(ioniclemon_basic_window basic_window.cpp)
target_link_libraries(ioniclemon_basic_window AperLambda::lambdacommon ioniclemon)