cmake_minimum_required(VERSION 3.21)

project(ComputerWorkshop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Sql Xml PrintSupport REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql Xml PrintSupport REQUIRED)

function(windeployqt target)
    string(TOLOWER ${CMAKE_BUILD_TYPE} buildtype)

    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND "${_qt5Core_install_prefix}/bin/windeployqt.exe"         
                --verbose 1
                --${buildtype}
                --no-svg
                --no-angle
                --no-opengl
                --no-opengl-sw
                --no-compiler-runtime
                --no-system-d3d-compiler
                \"$<TARGET_FILE:${target}>\"
        COMMENT "Deploying Qt libraries using windeployqt for compilation target '${target}' ..."
    )
endfunction()

file(GLOB_RECURSE PROJECT_SOURCES 
    ${CMAKE_CURRENT_LIST_DIR}/config/*
    ${CMAKE_CURRENT_LIST_DIR}/model/*
    ${CMAKE_CURRENT_LIST_DIR}/presenters/*
    ${CMAKE_CURRENT_LIST_DIR}/root/*
    ${CMAKE_CURRENT_LIST_DIR}/views/*
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/assets.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ComputerFirm
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(ComputerFirm SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(ComputerFirm
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ComputerFirm
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

set_target_properties(ComputerFirm PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
)

if(CMAKE_BUILD_TYPE STREQUAL Release)
    set_target_properties(ComputerFirm PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

if(WIN32)
    WINDEPLOYQT(ComputerFirm)
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ComputerFirm)
endif()
