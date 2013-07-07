cmake_minimum_required(VERSION 2.8.8)

project(qslsaver)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(PkgConfig)

set(VERSION 0.1)

pkg_check_modules(XCBSS xcb-screensaver)
link_directories(${XCBSS_LIBRARY_DIRS})
include_directories(${XCBSS_INCLUDE_DIRS})

pkg_check_modules(XCBDPMS xcb-dpms)
link_directories(${XCBDPMS_LIBRARY_DIRS})
include_directories(${XCBDPMS_INCLUDE_DIRS})

configure_file(data/qslsaver.desktop.in
               data/qslsaver.desktop)
configure_file(data/qslsaver-prefs.desktop.in
               data/qslsaver-prefs.desktop)

set(qslsaver_SRCS
    eventfilter.cpp
    main.cpp
    watcher.cpp
    worker.cpp)
add_executable(qslsaver ${qslsaver_SRCS})
qt5_use_modules(qslsaver Widgets)
target_link_libraries(qslsaver ${XCBSS_LIBRARIES} ${XCBDPMS_LIBRARIES})

set(pref_SRCS
    prefs.cpp
    options.cpp)
qt5_wrap_ui(pref_UIS options.ui)
add_executable(qslsaver-preferences ${pref_SRCS} ${pref_UIS})
qt5_use_modules(qslsaver-preferences Widgets)

install(FILES ${CMAKE_BINARY_DIR}/data/qslsaver.desktop
         DESTINATION /etc/xdg/autostart)
install(FILES ${CMAKE_BINARY_DIR}/data/qslsaver-prefs.desktop
         DESTINATION share/applications)
INSTALL(TARGETS qslsaver qslsaver-preferences
        RUNTIME DESTINATION bin)
