// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ProxyServer.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::Test;

class ProxyServerHandler : virtual public ProxyServerIf {
 public:
  ProxyServerHandler() {
    // Your initialization goes here
  }

  int32_t ping() {
    // Your implementation goes here
    printf("ping\n");
  }

  void echo(std::string& _return, const std::string& str) {
    // Your implementation goes here
    printf("echo\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ProxyServerHandler> handler(new ProxyServerHandler());
  shared_ptr<TProcessor> processor(new ProxyServerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

