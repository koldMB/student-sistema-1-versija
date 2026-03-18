cmake_minimum_required(VERSION 3.20)
project(deque-variantas)

set(CMAKE_CXX_STANDARD 17)

add_executable(dequeStudentai
        deque.cpp
        ../../Laikas.cpp
        ../../Laikas.h
        ../../IsvestisIvestis.cpp
        ../../IsvestisIvestis.h
        ../../Common.h
        ../../Common.cpp
        ../../Skaiciavimai.cpp
        ../../Skaiciavimai.h
        ../../klaiduValdymas.cpp
        ../../klaiduValdymas.h
)

target_include_directories(dequeStudentai PRIVATE ../../)
