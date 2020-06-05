#ifndef TEST_ASSIGNMENT_TCPCLIENT_H
#define TEST_ASSIGNMENT_TCPCLIENT_H

#include <src/client/BaseClient.h>

class TcpClient : public BaseClient
{
public:
  TcpClient();

  void send(const std::string &data, const std::string &address, int port) override;

private:
  bool connectToHost(const std::string &address, int port);
};


#endif //TEST_ASSIGNMENT_TCPCLIENT_H
