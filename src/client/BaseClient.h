#ifndef TEST_ASSIGNMENT_BASECLIENT_H
#define TEST_ASSIGNMENT_BASECLIENT_H

#include <src/server/IDataProcessor.h>

#include <netinet/in.h>
#include <memory>
#include <string>

class BaseClient
{
public:
  BaseClient(int socketType, int socketProtocol);
  virtual ~BaseClient();

  virtual void send(const std::string &data, const std::string &address, int port) = 0;
  void close();

protected:
  int socketId;

  bool init(int socketType, int socketProtocol);
  static sockaddr_in prepareAddress(int port);
};

#endif //TEST_ASSIGNMENT_BASECLIENT_H
