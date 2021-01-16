cmake_minimum_required(VERSION 3.17)
project(Clionprojects)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(Clionprojects
        Interpreter.cpp
        Interpreter.h
        Lexer.cpp
        Lexer.h
        OPS.h
        Parser.cpp
        Parser.h
        Token.h
        Token.cpp
        ENUMS.h
        Errors.h
        main.cpp)

