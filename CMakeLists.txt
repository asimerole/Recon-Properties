cmake_minimum_required(VERSION 3.16)

# Указываем путь к vcpkg для поиска библиотек и заголовков
set(VCPKG_ROOT "C:/development/vcpkg")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(Properties-Recon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем путь для поиска библиотек OpenSSL
set(OPENSSL_ROOT_DIR "${VCPKG_ROOT}/installed/x64-windows")
set(OPENSSL_LIBRARIES "${VCPKG_ROOT}/installed/x64-windows/lib")

# Найти OpenSSL
set(OPENSSL_INCLUDE_DIR "${VCPKG_ROOT}/installed/x64-windows/include/openssl")
find_package(OpenSSL REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network)

# Указываем директории с заголовками и библиотеками
include_directories("${VCPKG_ROOT}/installed/x64-windows-static/include")
link_directories("${VCPKG_ROOT}/installed/x64-windows/lib")

set(RESOURCES
    app_icon.rc
    resources.qrc
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    authorization.h
    authorization.cpp
    authorization.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Properties-Recon
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        app_icon.rc
        resources.qrc

    )
else()
    if(ANDROID)
        add_library(Properties-Recon SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Properties-Recon
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Линковка с необходимыми библиотеками
target_link_libraries(Properties-Recon PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
    curl
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Properties-Recon)
endif()
set_target_properties(Properties-Recon PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Properties-Recon
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Properties-Recon)
endif()
