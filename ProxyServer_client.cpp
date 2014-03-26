    #include "ProxyServer.h"  // As an example

    #include <transport/TSocket.h>
    #include <transport/TBufferTransports.h>
    #include <protocol/TBinaryProtocol.h>

    using namespace apache::thrift;
    using namespace apache::thrift::protocol;
    using namespace apache::thrift::transport;

   using namespace Test;

   int main(int argc, char **argv) {
     boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
     boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
     boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

     ProxyServerClient client(protocol);
     transport->open();
     client.ping();
     transport->close();

     return 0;
   }
