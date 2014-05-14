project(read_wav)
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS -std=c++1y)

find_package(Boost 1.55.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(READ_WAV_HDR
  speak_events.h
  speak_phonemes.h
  speak_visemes.h
)

set(READ_WAV_SRC
  read_wav.cpp
)

add_executable(read_wav ${READ_WAV_SRC} ${READ_WAV_HDR})
target_link_libraries(read_wav ${Boost_LIBRARIES})
