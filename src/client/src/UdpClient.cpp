#include <src/client/UdpClient.h>

#include <arpa/inet.h>

UdpClient::UdpClient() : BaseClient(SOCK_DGRAM, IPPROTO_UDP)
{
}

void UdpClient::send(const std::string &data, const std::string &address, int port)
{
  auto sa = prepareAddress(port);
  sa.sin_addr.s_addr = inet_addr(address.data());
  socklen_t sa_size = sizeof(sa);

  char reply[4096];
  int bytesSent = sendto(socketId, data.data(), data.length() + 1, 0, reinterpret_cast<sockaddr *>(&sa), sizeof(sa));
  if (bytesSent < 0)
  {
    std::printf("%s\n", "Failed to send the message");
  }
  else
  {
    if (recvfrom(socketId, reply, sizeof(reply), 0, reinterpret_cast<sockaddr *>(&sa), &sa_size) == -1)
    {
      std::printf("%s\n", "Failed to receive the response");
    }
    else
    {
      std::printf("%s\n", reply);
    }
  }
}
