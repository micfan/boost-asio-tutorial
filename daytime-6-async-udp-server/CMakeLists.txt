set(EXE daytime-6-async-udp-server)

add_executable(${EXE} main.cpp)
target_link_libraries(${EXE} ${LINK_LIBS})
