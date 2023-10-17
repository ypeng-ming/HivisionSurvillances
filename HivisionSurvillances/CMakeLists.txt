cmake_minimum_required(VERSION 3.5)

project(HivisionSurvillances VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core5Compat)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)
set(SDK_DIR "${PROJECT_SOURCE_DIR}/Include")
set(LIB_DIR "C:\\QTProjects\\HivisionSurvillances\\Lib")
include_directories(${SDK_DIR})
link_directories(${LIB_DIR})

add_library(HCNetSDKLib STATIC IMPORTED)
set_target_properties(HCNetSDKLib PROPERTIES IMPORTED_LOCATION "${LIB_DIR}/HCNetSDK.lib")

add_library(HCCoreLib STATIC IMPORTED)
set_target_properties(HCCoreLib PROPERTIES IMPORTED_LOCATION "${LIB_DIR}/HCCore.lib")

add_library(HCPreviewLib STATIC IMPORTED)
set_target_properties(HCPreviewLib PROPERTIES IMPORTED_LOCATION "${LIB_DIR}/HCPreview.lib")

add_library(PlayCtrlLib STATIC IMPORTED)
set_target_properties(PlayCtrlLib PROPERTIES IMPORTED_LOCATION "${LIB_DIR}/PlayCtrl.lib")

add_library(HCGeneralCfgMgrLib STATIC IMPORTED)
set_target_properties(HCGeneralCfgMgrLib PROPERTIES IMPORTED_LOCATION "${LIB_DIR}/HCGeneralCfgMgr.lib")

add_library(HCAlarmLib STATIC IMPORTED)
set_target_properties(HCAlarmLib PROPERTIES IMPORTED_LOCATION "${LIB_DIR}/HCAlarm.lib")


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HivisionSurvillances
       WIN32 MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        videobox.h videobox.cpp
    )
    #add_executable(HivisionSurvillances WIN32 ${PROJECT_SOURCES})
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET HivisionSurvillances APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(HivisionSurvillances SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(HivisionSurvillances
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(HivisionSurvillances PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(HivisionSurvillances PRIVATE Qt6::Core5Compat)
target_include_directories(HivisionSurvillances PRIVATE ${SDK_DIR})
target_link_libraries(HivisionSurvillances PRIVATE HCNetSDKLib
    HCCoreLib
    HCPreviewLib
    PlayCtrlLib
    HCGeneralCfgMgrLib
    HCAlarmLib)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.HivisionSurvillances)
endif()
set_target_properties(HivisionSurvillances PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS HivisionSurvillances
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HivisionSurvillances)
endif()
