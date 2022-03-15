cmake_minimum_required(VERSION 3.5)
project(wwise-audio)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

file(REMOVE_RECURSE "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-logg -lvorbis -pedantic -fno-permissive -pedantic-errors -Wall -Wextra -Wshadow -Wstrict-aliasing -Wno-misleading-indentation")


include_directories(include)

set(SOURCE
    src/codebook.cpp
    src/crc.c
    src/revorb.cpp
    src/ww2ogg.cpp
    src/wwriff.cpp
  )

add_library(wwise-audio SHARED ${SOURCE})
add_library(wwise-audio_static STATIC ${SOURCE})
add_executable(wwise-audio-converter ${SOURCE} src/main.cpp)

target_link_libraries(wwise-audio -logg -lvorbis)
target_link_libraries(wwise-audio_static -logg -lvorbis)
target_link_libraries(wwise-audio-converter -logg -lvorbis)