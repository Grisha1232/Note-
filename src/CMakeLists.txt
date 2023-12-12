cmake_minimum_required(VERSION 3.2)

project(note++)

set(CMAKE_CXX_STANDARD 20)
set(CMALE_CXX_STANDARD_REQUIERED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(note++
    main.cpp
)

add_library(Views views/MainWindow.h views/MainWindow.cpp)
add_library(Models models/file.h models/file.cpp models/errorFile.h)

target_link_libraries(note++ PRIVATE Qt6::Widgets)
target_link_libraries(Views PRIVATE Qt6::Widgets)

target_link_libraries(note++ PRIVATE Views)
target_link_libraries(Models PRIVATE Views)
target_link_libraries(Views PRIVATE Models)


set_target_properties(note++ PROPERTIES
	WIN32_EXECUTABLE ON
	MACOSX_BUNDLE ON
)
