#include <src/server/TcpServer.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <cassert>
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include <future>
#include <unistd.h>
#include <src/server/SumDataProcessor.h>
//#include <cstdlib>

#define CHECK(x, text)\
if (x == -1)\
{\
  std::printf(text);\
  std::printf("%d\n", errno);\
  exit(-1);\
}

#define ASSIGN_AND_CHECK(dest, x, text)\
const int dest = x;\
CHECK(dest, text)

TcpServer::TcpServer(const int port, std::unique_ptr<IDataProcessor> &&processor) : BaseServer(port,
                                                                                               std::move(processor))
{
}

TcpServer::~TcpServer()
{
  TcpServer::stop();
}

void TcpServer::start()
{
  sockaddr_in sa;
  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(m_port);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);

//  ASSIGN_AND_CHECK(id, socket(AF_INET, SOCK_STREAM, IPPROTO_TCP), "Failed to create a socket\n")
//  m_socketId.store(id);
//  ASSIGN_AND_CHECK(flags, fcntl(m_socketId, F_GETFL), "Could not get flags\n")
//  CHECK(fcntl(m_socketId, F_SETFL, flags | O_NONBLOCK), "Could not set flags\n")
  createSocket(SOCK_STREAM, IPPROTO_TCP);
  CHECK(bind(m_socketId, reinterpret_cast<sockaddr *>(&sa), sizeof(sa)), "Failed to bind\n")
  CHECK(listen(m_socketId, 100), "Failed to start server\n")

  m_isOpen.store(true);
  routine();
}

void TcpServer::routine()
{
  char buffer[1025];
  while(m_isOpen.load())
  {
    int clientId = accept(m_socketId, nullptr, nullptr);
    if (clientId == -1)
    {
      if (errno != EWOULDBLOCK)
      {
        std::printf("Error when accepting connection\n");
        std::printf("%d\n", errno);
      }
    }
    else
    {
      memset(buffer, 0, sizeof(buffer));
      if(receive(clientId, buffer, sizeof(buffer)))
      {
        std::thread thread{&TcpServer::process, this, clientId, std::string{buffer}};
        thread.detach();
      }
    }
  }
}

bool TcpServer::receive(int socketId, char *buffer, size_t maxlen)
{
  return (read(socketId, buffer, maxlen) != -1);
}

void TcpServer::send(int socketId, const std::string &data)
{
  if(m_isOpen.load())
    ::send(socketId, data.data(), data.length() + 1, 0);
}
