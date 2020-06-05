#ifndef TEST_ASSIGNMENT_BASESERVER_H
#define TEST_ASSIGNMENT_BASESERVER_H

#include <src/server/IDataProcessor.h>

#include <atomic>
#include <cstdint>
#include <memory>

class BaseServer
{
public:
  BaseServer(uint16_t port, std::unique_ptr<IDataProcessor> &&processor);
  virtual ~BaseServer() = default;

  /**
   * Starts the server.
   * @return socket descriptor
   */
  virtual void start() = 0;

  /**
   * Stops the server.
   */
  void stop();

protected:
  const int m_port;
  const std::unique_ptr<IDataProcessor> m_processor;
  int m_socketId{-1};
  std::atomic_bool m_isOpen{false};

  void createSocket(int socketType, int protocol, bool nonBlocking = true);
  void process(int socketId, const std::string &data);

  virtual bool receive(int socketId, char *buffer, size_t maxlen) = 0;
  virtual void send(int socketId, const std::string &data) = 0;
};

#endif //TEST_ASSIGNMENT_BASESERVER_H
