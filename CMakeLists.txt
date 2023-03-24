cmake_minimum_required(VERSION 3.1.0)

project(AndroidTools VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui  REQUIRED)
find_package(Dtk COMPONENTS Widget REQUIRED)
find_package(Dtk COMPONENTS Core REQUIRED)
find_package(Dtk COMPONENTS Gui)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE HEAD include/*.h)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/widget)
include_directories(${CMAKE_SOURCE_DIR}/include/tools)
include_directories(${CMAKE_SOURCE_DIR}/include/Thread)

add_executable(${PROJECT_NAME}
        ${SRC} ${HEAD})

target_link_libraries(AndroidTools PRIVATE
    Qt5::Widgets
    Qt5::Gui
    ${DtkGui_LIBRARIES}
    ${DtkCore_LIBRARIES}
    ${DtkWidget_LIBRARIES}
) # 链接库
