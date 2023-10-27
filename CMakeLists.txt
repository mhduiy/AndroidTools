cmake_minimum_required(VERSION 3.1.0)

project(AndroidTools VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("********************************************")
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	message("current platform is Linux!")
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message("current platform is Windows!")
    set(Qt5_DIR C:\\Qt\\Qt5.14.2\\5.14.2\\mingw73_64\\lib\\cmake\\Qt5)
endif ()
message("********************************************")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui  REQUIRED)
find_package(Qt5 COMPONENTS Core  REQUIRED)
find_package(Qt5 COMPONENTS Network  REQUIRED)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE HEAD src/*.h)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(RES_LIST ${CMAKE_SOURCE_DIR}/res/myres.qrc)

add_executable(${PROJECT_NAME} ${SRC} ${HEAD} ${RES_LIST})

add_executable(TestApp  ${SRC} ${HEAD} ${RES_LIST})

target_link_libraries(AndroidTools PRIVATE
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
    Qt5::Network
)
