cmake_minimum_required(VERSION 3.10)
project(OOProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(terminal
    main.cpp
    src/Entry.cpp
    src/Directory.cpp
    src/SingleLineFile.cpp
    src/MultiLineFile.cpp
    src/PostponedFile.cpp
    src/Terminal.cpp
)
