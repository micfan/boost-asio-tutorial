set(EXE daytime-2-tcp-server)

add_executable(${EXE} main.cpp)
target_link_libraries(${EXE} ${LINK_LIBS})
