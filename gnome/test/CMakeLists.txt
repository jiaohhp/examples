cmake_minimum_required(VERSION 2.8)

project(softclient)
find_package (PkgConfig REQUIRED)

pkg_check_modules (GTK3 REQUIRED gtk+-3.0)
include_directories (${GTK3_INCLUDE_DIRS})
link_libraries (${GTK3_LIBRARIES})

add_executable(iconview main.c iconview.c)
