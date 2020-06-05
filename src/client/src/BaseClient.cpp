#include <src/client/BaseClient.h>

#include <cassert>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

BaseClient::BaseClient(int socketType, int socketProtocol)
{
  assert(init(socketType, socketProtocol));
}

BaseClient::~BaseClient()
{
  close();
}

bool BaseClient::init(int socketType, int socketProtocol)
{
  socketId = socket(PF_INET, socketType, socketProtocol);
  if(socketId == -1)
  {
    std::printf("%s\n", "Cannot create socketId");
    return false;
  }
  return true;
}

void BaseClient::close()
{
  ::close(socketId);
}

sockaddr_in BaseClient::prepareAddress(const int port)
{
  sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  return sa;
}
