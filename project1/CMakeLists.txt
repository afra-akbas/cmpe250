cmake_minimum_required(VERSION 2.8.12.2)
project(project1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-std=c++11")

set(SOURCE_FILES main.cpp LinkedList.cpp LinkedList.h Member.cpp Member.h SurveyClass.cpp SurveyClass.h Node.cpp Node.h)
add_executable(project1 ${SOURCE_FILES})
