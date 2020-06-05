#include <src/client/TcpClient.h>
#include <src/client/UdpClient.h>

#include <src/utils/OptionParser.h>

#include <getopt.h>
#include <cassert>

int main(int argc, char **argv)
{
  BaseClient *client;

  auto clientCreator = [&client]()
    {
      const std::string protocol{optarg};
      if (protocol == "tcp")
        client = new TcpClient;
      else if (protocol == "udp")
        client = new UdpClient;
      else
      {
        std::printf("%s\n", "Wrong protocol");
        exit(-1);
      }
    };

  int port = -1;
  std::string address;
  OptionsParser op;
  op.addOption({"protocol", required_argument, nullptr, 'p'}, std::move(clientCreator));
  op.addOption({"address", required_argument, nullptr, 'a'}, [&address]()
    { address = std::string(optarg); });
  op.addOption({"port", required_argument, nullptr, 'b'}, [&port]()
    { port = std::stoi(optarg); });
  op.parseOptions(argc, argv);
  assert(port != -1);
  assert(!address.empty());
  assert(client);

  std::string message;
  do
  {
    std::printf("Input the phrase:\n");
    getline(std::cin, message);
    if(!message.empty())
      client->send(message, address, port);
  } while (!message.empty());
  client->close();
}

