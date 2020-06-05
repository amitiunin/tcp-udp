#ifndef TEST_ASSIGNMENT_UDPCLIENT_H
#define TEST_ASSIGNMENT_UDPCLIENT_H

#include <src/client/BaseClient.h>

class UdpClient : public BaseClient
{
public:
  UdpClient();

  void send(const std::string &data, const std::string &address, int port) override;
};


#endif //TEST_ASSIGNMENT_UDPCLIENT_H
