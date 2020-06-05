#ifndef TEST_ASSIGNMENT_TCPSERVER_H
#define TEST_ASSIGNMENT_TCPSERVER_H

#include <src/server/BaseServer.h>
#include <cstdint>
#include <atomic>

class TcpServer final: public BaseServer
{
public:
  explicit TcpServer(int port, std::unique_ptr<IDataProcessor> &&processor);
  ~TcpServer() override;

  void start() override;

  bool receive(int socketId, char *buffer, size_t maxlen) override;
  void send(int socketId, const std::string &data) override;

private:
  void routine();
};

#endif //TEST_ASSIGNMENT_TCPSERVER_H
