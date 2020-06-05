add_executable(server
        src/SumDataProcessor.cpp
        src/BaseServer.cpp
        src/TcpServer.cpp
        src/UdpServer.cpp
        src/main.cpp
        )
target_link_libraries(server pthread)