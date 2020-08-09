cmake_minimum_required(VERSION 3.1)
project(testapp C)
add_library(Linux STATIC
    os_api.c
)
