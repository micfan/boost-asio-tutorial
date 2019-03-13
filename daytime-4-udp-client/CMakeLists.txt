set(EXE daytime-4-udp-client)

add_executable(${EXE} main.cpp)
target_link_libraries(${EXE} ${LINK_LIBS})
