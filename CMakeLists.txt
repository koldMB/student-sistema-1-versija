cmake_minimum_required(VERSION 3.20)
project(studentu-sistema)

set(CMAKE_CXX_STANDARD 17)

add_executable(studentuSistema
        Main.cpp
        Laikas.cpp
        Laikas.h
        IsvestisIvestis.cpp
        IsvestisIvestis.h
        Common.h
        Common.cpp
        Skaiciavimai.cpp
        Skaiciavimai.h
        klaiduValdymas.cpp
        klaiduValdymas.h
)