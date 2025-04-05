cmake_minimum_required(VERSION 3.10)
project(CGALBooleanOperationsVisualizerQT)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt with all required components
find_package(Qt5 COMPONENTS Widgets Gui Core REQUIRED)

# Qt setup
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find CGAL and mathematical libraries
find_package(CGAL REQUIRED)
find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)

# Include directories
include_directories(${CGAL_INCLUDE_DIRS})
include_directories(${GMP_INCLUDE_DIRS})
include_directories(${MPFR_INCLUDE_DIRS})
include_directories(include)

# Command line version
add_executable(boolean_operations 
    main.cpp
    src/BooleanOperations.cpp
)

# Link libraries for command line version
target_link_libraries(boolean_operations 
    ${CGAL_LIBRARIES}
    ${GMP_LIBRARIES}
    ${MPFR_LIBRARIES}
)

# GUI version
add_executable(boolean_operations_gui
    src/BooleanOperationsGUI.cpp
    src/BooleanOperations.cpp
)

# Link libraries for GUI version
target_link_libraries(boolean_operations_gui
    ${CGAL_LIBRARIES}
    ${GMP_LIBRARIES}
    ${MPFR_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
)

# Installation
install(TARGETS boolean_operations boolean_operations_gui DESTINATION bin)