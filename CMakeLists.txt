cmake_minimum_required(VERSION 3.12)
project(boost-asio-tutorial)

set(CMAKE_CXX_STANDARD 11)

set (THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)

find_package(Boost COMPONENTS system thread)
IF(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
ENDIF(Boost_FOUND)

set(LINK_LIBS Threads::Threads
        boost_thread)

add_subdirectory(timer-1)
add_subdirectory(timer-2-async)
add_subdirectory(timer-3-async-bind-handler)
add_subdirectory(timer-4-async-member-handler)
add_subdirectory(timer-5-async-thread-handler)

add_subdirectory(daytime-1-tcp-client)
add_subdirectory(daytime-2-tcp-server)
add_subdirectory(daytime-3-async-tcp-server)
add_subdirectory(daytime-4-udp-client)