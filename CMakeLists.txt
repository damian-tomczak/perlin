cmake_minimum_required(VERSION 3.11)

project(perlin VERSION 0.0.1 LANGUAGES CXX)

if(NOT DEFINED ${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SRC_FILES *.cpp)

include(FetchContent)

FetchContent_Declare(matplotlib_cpp
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
)

FetchContent_MakeAvailable(matplotlib_cpp)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)

target_link_libraries(${PROJECT_NAME}
    matplotlib_cpp
)

set(MATPLOTLIB_CPP_PATH ${FETCHCONTENT_BASE_DIR}/matplotlib_cpp-src)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${MATPLOTLIB_CPP_PATH}
)

if(UNIX)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<NOT:$<CONFIG:Debug>>:-DNDEBUG>
        $<IF:$<CONFIG:Debug>, -g, -O3>
        -Wall -Werror -Wno-unused-function -Wfatal-errors
    )
endif()