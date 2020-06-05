#include <src/server/BaseServer.h>

#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

BaseServer::BaseServer(uint16_t port, std::unique_ptr<IDataProcessor> &&processor) : m_port(port),
                                                                                     m_processor(std::move(processor))
{
}

void BaseServer::stop()
{
  m_isOpen.store(false);
  ::close(m_socketId);
}

void BaseServer::createSocket(int socketType, int protocol, bool nonBlocking)
{
  const int id = socket(AF_INET, socketType, protocol);
  if(id == -1)
  {
    std::printf("Failed to create a socket\n%d\n", errno);
    exit(-1);
  }
  m_socketId = id;

  if (nonBlocking)
  {
    const int flags = fcntl(m_socketId, F_GETFL);
    if (flags == -1)
    {
      std::printf("Could not get flags\n%d\n", errno);
      stop();
      exit(-1);
    }

    if (fcntl(m_socketId, F_SETFL, flags | O_NONBLOCK) == -1)
    {
      std::printf("Could not set flags\n%d\n", errno);
      stop();
      exit(-1);
    }
  }
}

void BaseServer::process(int socketId, const std::string &data)
{
  std::printf("%s\n", data.data());
  const auto reply = m_processor->process(data);
  std::printf("%s\n", reply.data());
  send(socketId, reply);
}
