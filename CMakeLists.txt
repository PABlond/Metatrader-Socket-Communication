cmake_minimum_required(VERSION 3.16.3)
project(MqlSocketCommunication)
file(GLOB SRC CONFIGURE_DEPENDS "src/*.cpp")
add_executable ( server ${SRC})