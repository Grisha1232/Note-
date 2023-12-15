cmake_minimum_required(VERSION 3.2)
project(note++)

set(CMAKE_CXX_STANDARD 20)
set(CMALE_CXX_STANDARD_REQUIERED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(src)

