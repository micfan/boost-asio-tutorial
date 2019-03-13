set(EXE daytime-1-tcp-client)

add_executable(${EXE} main.cpp)
target_link_libraries(${EXE} ${LINK_LIBS})
