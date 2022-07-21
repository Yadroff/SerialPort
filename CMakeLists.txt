cmake_minimum_required(VERSION 3.22)
project(SerialPort)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        SerialPort)

add_executable(SerialPort main.cpp SerialPort.cpp)
target_link_libraries(SerialPort
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::SerialPort
        )

