#ifndef TEST_ASSIGNMENT_UDPSERVER_H
#define TEST_ASSIGNMENT_UDPSERVER_H

#include <src/server/BaseServer.h>
#include <src/server/IDataProcessor.h>

#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>

class UdpServer : public BaseServer
{
public:
  explicit UdpServer(int port, std::unique_ptr<IDataProcessor> &&processor);

  void start() override;

  bool receive(int socketId, char *buffer, size_t maxlen) override;
  void send(int socketId, const std::string &data) override;

private:
  sockaddr_in m_sa;
};

#endif //TEST_ASSIGNMENT_UDPSERVER_H
