cmake_minimum_required(VERSION 3.12)
project(wwise-audio-tools)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(
    include
    libogg/include
    libvorbis/include
  )

add_definitions(-DKS_STR_ENCODING_NONE)

set(SOURCE
    src/codebook.cpp
    src/crc.c
    src/revorb.cpp
    src/ww2ogg.cpp
    src/wwriff.cpp
    src/wwiseaudiotools.cpp
    src/packed_codebooks.cpp
		src/kaitaistream.cpp
		src/bnk.cpp
  )

find_package(Catch2 3)

add_subdirectory(libogg EXCLUDE_FROM_ALL)
add_subdirectory(libvorbis EXCLUDE_FROM_ALL)

add_library(wwise-audio SHARED ${SOURCE})
add_library(wwise-audio_static STATIC ${SOURCE})
add_executable(wwise-audio-tools ${SOURCE} src/main.cpp)

target_link_libraries(wwise-audio ogg vorbis)
target_link_libraries(wwise-audio_static ogg vorbis)
target_link_libraries(wwise-audio-tools ogg vorbis)

if(Catch2_FOUND)
  add_executable(tests ${SOURCE} tests/test.cpp)
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
  file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/testdata DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()