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

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui  REQUIRED)
find_package(Qt5 COMPONENTS Core  REQUIRED)
find_package(Qt5 COMPONENTS Network  REQUIRED)

# file(GLOB_RECURSE SRC src/*.cpp)
# file(GLOB_RECURSE HEAD src/*.h)

aux_source_directory(${CMAKE_SOURCE_DIR}/src/infoPanel/ infoPanelCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/AppManage/ AppManageCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/DeviceControl/ DeviceControlCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/FlashingTool/ FlashingToolCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/ScreenMirroring/ ScreenMirroringCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/TerminalTool/ TerminalToolCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/Global/ GlobalCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/MADB/ MADB)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/MainWindow/ MainWindowCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/Mcomponent/ McomponentCpp)
aux_source_directory(${CMAKE_SOURCE_DIR}/src/test/ testCpp)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/MComponent)

set(RES_LIST ${CMAKE_SOURCE_DIR}/src/MComponent/res/mComponent.qrc)

message("********************************************")

add_executable(
    ${PROJECT_NAME}
    ${infoPanelCpp}
    ${AppManageCpp}
    ${DeviceControlCpp}
    ${FlashingToolCpp}
    ${ScreenMirroringCpp}
    ${TerminalToolCpp}
    ${GlobalCpp}
    ${MADB}
    ${MainWindowCpp}
    ${McomponentCpp}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${RES_LIST})

add_executable(TestApp
    ${infoPanelCpp}
    ${AppManageCpp}
    ${DeviceControlCpp}
    ${FlashingToolCpp}
    ${ScreenMirroringCpp}
    ${TerminalToolCpp}
    ${GlobalCpp}
    ${MADB}
    ${MainWindowCpp}
    ${McomponentCpp}
    ${testCpp}
    ${RES_LIST})

target_link_libraries(AndroidTools PRIVATE
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
    Qt5::Network
)

target_link_libraries(TestApp PRIVATE
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
    Qt5::Network
)
