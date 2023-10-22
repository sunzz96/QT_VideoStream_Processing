cmake_minimum_required(VERSION 3.5)

project(QT_VideoStream_Processing VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Multimedia MultimediaWidgets)

# 3rdparty: opencv
SET(OPENCV_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/include)
include_directories(${OPENCV_INCLUDE_DIR})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QT_VideoStream_Processing
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        basecamera.h basecamera.cpp
        imgprocessor.h imgprocessor.cpp
        proctask.h
        lowleveltasks.h lowleveltasks.cpp
        encoder.h encoder.cpp
        servercore.h servercore.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QT_VideoStream_Processing APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QT_VideoStream_Processing SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QT_VideoStream_Processing
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(QT_VideoStream_Processing PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
)

if(APPLE AND NOT IOS)
    set_target_properties(QT_VideoStream_Processing PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/macos/Info.plist.in"
    )
elseif(IOS)
    set_target_properties(QT_VideoStream_Processing PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/ios/Info.plist.in"
    )
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.QT_VideoStream_Processing)
endif()
set_target_properties(QT_VideoStream_Processing PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QT_VideoStream_Processing
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QT_VideoStream_Processing)
endif()

# link 3rdparty
if(APPLE AND NOT IOS)
    file(GLOB 3RD_LIB "./3rdparty/lib_macos_aarch64/*.dylib")
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC ${3RD_LIB})
