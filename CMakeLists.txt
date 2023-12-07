cmake_minimum_required(VERSION 3.25.1)
project(DocScanner CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenCV REQUIRED)
add_executable(DocScanner main.cpp File.cpp DocManager.cpp FrameCorrector.cpp)
target_link_libraries(DocScanner ${OpenCV_LIBS})