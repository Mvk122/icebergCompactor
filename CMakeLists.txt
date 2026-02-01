cmake_minimum_required(VERSION 4.1)
project(icebergCompactor)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(icebergCompactor main.cpp
        ParquetReader.cpp
        ParquetReader.h
        EnvReader.cpp
        EnvReader.h
)
