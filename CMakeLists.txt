cmake_minimum_required(VERSION 3.19)
project(cdns C)

set(CMAKE_C_STANDARD 11)

add_executable(cdns main.c dns.h dns.c hashdns.h hashdns.c)