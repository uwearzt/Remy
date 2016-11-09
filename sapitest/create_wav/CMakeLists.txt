project(create_wav)
cmake_minimum_required(VERSION 3.4)

set(BOOST_ROOT "C:\\local\\boost_1_62_0")
set(BOOST_LIBRARYDIR "C:\\local\\boost_1_62_0\\lib32-msvc-14.0")
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.62.0 COMPONENTS program_options REQUIRED) 

include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D _UNICODE /D UNICODE")

add_executable(create_wav create_wav.cpp)
target_link_libraries(create_wav ${Boost_LIBRARIES})

