cmake_minimum_required(VERSION 2.8)

project(poco-event-which-thread)
add_executable(${PROJECT_NAME} "main.cpp")

# link poco
find_package(Poco COMPONENTS Foundation Net Util)
if(Poco)
    target_link_libraries(${PROJECT_NAME} Poco::Foundation Poco::Net Poco::Util)
else()
    message(WARNING "jxh:poco is not supported by cmake, we find it manually.")
    foreach(i   Foundation Net Util)
        unset(libi CACHE)
        find_library(libi Poco${i})
        if(libi)
            target_link_libraries(${PROJECT_NAME} ${libi})
        else()
            message(FATAL_ERROR "jxh:not found ${i} lib")
        endif()
    endforeach()
endif()
