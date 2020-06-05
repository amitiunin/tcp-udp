#include <src/server/TcpServer.h>
#include <src/server/UdpServer.h>
#include <src/server/SumDataProcessor.h>

#include <src/utils/OptionParser.h>

#include <thread>
#include <cassert>
#include <vector>

class ServerController
{
public:
  ServerController() = default;

  void addServer(std::unique_ptr<BaseServer> &&server)
  {
    servers.push_back(std::move(server));
  }

  void addServer(BaseServer *server)
  {
    servers.emplace_back(server);
  }

  void start()
  {
    for (auto &s : servers)
      std::thread{&BaseServer::start, s.get()}.detach();
  }

  void stop()
  {
    for (auto &s : servers)
      s->stop();
  }

private:
  std::vector<std::unique_ptr<BaseServer>> servers;
};

int main(int argc, char **argv)
{
  int tcpPort = -1;
  int udpPort = -1;

  OptionsParser op;
  op.addOption({"tcp_port", required_argument, nullptr, 't'},
               [&tcpPort]()
                 { tcpPort = std::stoi(optarg); });
  op.addOption({"udp_port", required_argument, nullptr, 'u'},
               [&udpPort]()
                 { udpPort = std::stoi(optarg); });
  op.parseOptions(argc, argv);
  assert(tcpPort > 0 && udpPort > 0);

  ServerController controller;
  controller.addServer(new TcpServer{tcpPort, std::make_unique<SumDataProcessor>()});
  controller.addServer(new UdpServer{udpPort, std::make_unique<SumDataProcessor>()});
  controller.start();
  getchar();
  controller.stop();
  return 0;
}
