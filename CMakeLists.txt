cmake_minimum_required(VERSION 3.26.4)
project(COP3530_Project_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(COP3530_Project_3 main.cpp
        anime.cpp
        anime.h
        animeList.cpp
        animeList.h
        animeDataLoader.cpp
        animeDataLoader.h
)
