set(EXE daytime-5-udp-server)

add_executable(${EXE} main.cpp)
target_link_libraries(${EXE} ${LINK_LIBS})
