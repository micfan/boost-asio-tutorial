set(EXE daytime-3-async-tcp-server)

add_executable(${EXE} main.cpp)
target_link_libraries(${EXE} ${LINK_LIBS})
