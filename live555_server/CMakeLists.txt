cmake_minimum_required(VERSION 2.8)

project(live555_server)
add_executable(${PROJECT_NAME} "main.cpp" "jcrtspserver.cpp" "jcrtspserver.h")


find_package(PkgConfig REQUIRED)

pkg_check_modules(Live555 REQUIRED IMPORTED_TARGET live555)
target_link_libraries(${PROJECT_NAME} PkgConfig::Live555)
