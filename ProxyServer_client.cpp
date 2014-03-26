    #include "ProxyServer.h"  // As an example

    #include <transport/TSocket.h>
    #include <transport/TBufferTransports.h>
    #include <protocol/TBinaryProtocol.h>

    #include <iostream>
    #include <string>


    using namespace apache::thrift;
    using namespace apache::thrift::protocol;
    using namespace apache::thrift::transport;

    using namespace std;

   using namespace Test;

   int main(int argc, char **argv) {
     boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
     boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
     boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

     ProxyServerClient client(protocol);
     transport->open();
     client.ping();
     
     string str;
     client.echo(str, "Sandeep Manchem");
     transport->close();

     return 0;
   }
