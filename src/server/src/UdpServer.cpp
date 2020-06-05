#include <src/server/UdpServer.h>
#include <netinet/in.h>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include <thread>

UdpServer::UdpServer(const int port, std::unique_ptr<IDataProcessor> &&processor) : BaseServer(port,
                                                                                               std::move(processor))
{
}

void UdpServer::start()
{
  sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(m_port);
  m_sa = sa;

  createSocket(SOCK_DGRAM, IPPROTO_UDP);
  if (bind(m_socketId, reinterpret_cast<sockaddr *>(&sa), sizeof(sa)) == -1)
  {
    std::printf("%s\n", "Failed to bind");
    std::printf("%d\n", errno);
    stop();
    exit(-1);
  }
  m_isOpen.store(true);

  char buffer[1025];
  while(m_isOpen.load())
  {
    if(receive(m_socketId, buffer, sizeof(buffer)))
    {
      std::thread thread{&UdpServer::process, this, m_socketId, std::string{buffer}};
      thread.detach();
    }
  }
}

bool UdpServer::receive(int socketId, char *buffer, size_t maxlen)
{
  static socklen_t sa_size = sizeof(m_sa);
  return (recvfrom(m_socketId, reinterpret_cast<void *>(buffer), maxlen, 0,
                  reinterpret_cast<sockaddr *>(&m_sa), &sa_size) != -1);
}

void UdpServer::send(int socketId, const std::string &data)
{
  if(m_isOpen.load())
    sendto(socketId, data.data(), data.length() + 1, 0, reinterpret_cast<sockaddr *>(&m_sa), sizeof(sockaddr_in));
}

