#include <src/client/TcpClient.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>

TcpClient::TcpClient() : BaseClient(SOCK_STREAM, IPPROTO_TCP)
{
}

bool TcpClient::connectToHost(const std::string &address, const int port)
{
  auto sa = prepareAddress(port);
  inet_pton(AF_INET, address.data(), &sa.sin_addr);

  if(connect(socketId, reinterpret_cast<sockaddr *>(&sa), sizeof(sa)) == -1)
  {
    std::printf("%s\n", "Cannot connect to host");
    ::close(socketId);
    return false;
  }
  return true;
}

void TcpClient::send(const std::string &data, const std::string &address, const int port)
{
  if (connectToHost(address, port))
  {
    if (::send(socketId, data.data(), data.size() + 1, 0) == -1)
    {
      std::printf("%s\n", "Failed to send data");
    }
    else
    {
      char reply[4096]; // overkill
      memset(&reply, 0, sizeof(reply));
      if (recv(socketId, reply, sizeof(reply), 0) == -1)
      {
        std::printf("%s\n", "Failed to receive the response");
      }
      else
      {
        std::printf("%s\n", reply);
      }
    }
  }
}
