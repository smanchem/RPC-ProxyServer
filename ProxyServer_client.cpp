    #include "ProxyServer.h"  // As an example

    #include <transport/TSocket.h>
    #include <transport/TBufferTransports.h>
    #include <protocol/TBinaryProtocol.h>

    #include <iostream>
    #include <string>
    #include <sys/time.h>

    using namespace apache::thrift;
    using namespace apache::thrift::protocol;
    using namespace apache::thrift::transport;

    using namespace std;

   using namespace Test;

   int main(int argc, char **argv) {
     boost::shared_ptr<TSocket> socket(new TSocket("128.61.123.99", 9090));
     boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
     boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

     ProxyServerClient client(protocol);
     transport->open();
     client.ping();
     struct timeval t1,t2;
     string str;
     gettimeofday(&t1,NULL);
     client.echo(str, argv[1]);
     gettimeofday(&t2,NULL);
     //cout << str << endl;
     transport->close();
     cout<<"\n Data obtained from "<<argv[1]<<" in "<<(t2.tv_sec*1000000.0 + t2.tv_usec - t1.tv_sec*1000000 - t1.tv_usec);
     return 0;
   }
