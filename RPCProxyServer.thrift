#!/usr/local/bin/thrift --gen cpp

namespace cpp Test

service ProxyServer {
      i32 ping(),
      string echo(1:string str)
}
