cmake_minimum_required(VERSION 3.10)
project(palette)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -std=c++17 -lboost_system -lboost_filesystem -lstdc++fs")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -Werror -std=c++17 \
                              =lboost_system -lboost_filesystem -lstdc++fs")
set(Boost_FILESYSTEM "/usr/local/lib/libboost_filesystem.a")
find_package(OpenCV REQUIRED)
find_package(Boost ${BOOST_VERSION} COMPONENTS filesystem system REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/)

file(GLOB ALL_SOURCES ${SRC_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

file(GLOB ALL_HEADERS ${SRC_INCLUDE}/*.h)


add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_HEADERS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} )
target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM})
