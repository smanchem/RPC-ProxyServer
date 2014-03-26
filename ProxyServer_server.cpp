// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "ProxyServer.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <iostream>
#include <string>
#include <cstring>
#include "CacheDataStructures.cpp"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::Test;

using namespace std;

/*
Comment the following statement when Caching is not required.
*/
#define CACHING

class ProxyServerHandler : virtual public ProxyServerIf {
 public:
  Cache pageCache;
  ProxyServerHandler() {
    // Your initialization goes here
  }

  int32_t ping() {
    // Your implementation goes here
    printf("ping\n");
  }

  void echo(std::string& _return, const std::string& str) {
    // Your implementation goes here
    cout << "echo: " << str << endl;

#ifdef CACHING
    _return = pageCache.search_page(str);
    printf("Page sent to client\n");
    return;
#endif
    char *url = new char[str.size() + 1];
    std::copy(str.begin(), str.end(), url);
    url[str.size()] = '\0';
    char *body = getContent(url); 
    std::string s(body);
    _return = s;
    free(body);
    printf("Page sent to client\n");
    return;
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

