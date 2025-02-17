/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef ProxyServer_H
#define ProxyServer_H

#include <thrift/TDispatchProcessor.h>
#include "RPCProxyServer_types.h"

namespace Test {

class ProxyServerIf {
 public:
  virtual ~ProxyServerIf() {}
  virtual int32_t ping() = 0;
  virtual void echo(std::string& _return, const std::string& str) = 0;
};

class ProxyServerIfFactory {
 public:
  typedef ProxyServerIf Handler;

  virtual ~ProxyServerIfFactory() {}

  virtual ProxyServerIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(ProxyServerIf* /* handler */) = 0;
};

class ProxyServerIfSingletonFactory : virtual public ProxyServerIfFactory {
 public:
  ProxyServerIfSingletonFactory(const boost::shared_ptr<ProxyServerIf>& iface) : iface_(iface) {}
  virtual ~ProxyServerIfSingletonFactory() {}

  virtual ProxyServerIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(ProxyServerIf* /* handler */) {}

 protected:
  boost::shared_ptr<ProxyServerIf> iface_;
};

class ProxyServerNull : virtual public ProxyServerIf {
 public:
  virtual ~ProxyServerNull() {}
  int32_t ping() {
    int32_t _return = 0;
    return _return;
  }
  void echo(std::string& /* _return */, const std::string& /* str */) {
    return;
  }
};


class ProxyServer_ping_args {
 public:

  ProxyServer_ping_args() {
  }

  virtual ~ProxyServer_ping_args() throw() {}


  bool operator == (const ProxyServer_ping_args & /* rhs */) const
  {
    return true;
  }
  bool operator != (const ProxyServer_ping_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ProxyServer_ping_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ProxyServer_ping_pargs {
 public:


  virtual ~ProxyServer_ping_pargs() throw() {}


  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ProxyServer_ping_result__isset {
  _ProxyServer_ping_result__isset() : success(false) {}
  bool success;
} _ProxyServer_ping_result__isset;

class ProxyServer_ping_result {
 public:

  ProxyServer_ping_result() : success(0) {
  }

  virtual ~ProxyServer_ping_result() throw() {}

  int32_t success;

  _ProxyServer_ping_result__isset __isset;

  void __set_success(const int32_t val) {
    success = val;
  }

  bool operator == (const ProxyServer_ping_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ProxyServer_ping_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ProxyServer_ping_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ProxyServer_ping_presult__isset {
  _ProxyServer_ping_presult__isset() : success(false) {}
  bool success;
} _ProxyServer_ping_presult__isset;

class ProxyServer_ping_presult {
 public:


  virtual ~ProxyServer_ping_presult() throw() {}

  int32_t* success;

  _ProxyServer_ping_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _ProxyServer_echo_args__isset {
  _ProxyServer_echo_args__isset() : str(false) {}
  bool str;
} _ProxyServer_echo_args__isset;

class ProxyServer_echo_args {
 public:

  ProxyServer_echo_args() : str() {
  }

  virtual ~ProxyServer_echo_args() throw() {}

  std::string str;

  _ProxyServer_echo_args__isset __isset;

  void __set_str(const std::string& val) {
    str = val;
  }

  bool operator == (const ProxyServer_echo_args & rhs) const
  {
    if (!(str == rhs.str))
      return false;
    return true;
  }
  bool operator != (const ProxyServer_echo_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ProxyServer_echo_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class ProxyServer_echo_pargs {
 public:


  virtual ~ProxyServer_echo_pargs() throw() {}

  const std::string* str;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ProxyServer_echo_result__isset {
  _ProxyServer_echo_result__isset() : success(false) {}
  bool success;
} _ProxyServer_echo_result__isset;

class ProxyServer_echo_result {
 public:

  ProxyServer_echo_result() : success() {
  }

  virtual ~ProxyServer_echo_result() throw() {}

  std::string success;

  _ProxyServer_echo_result__isset __isset;

  void __set_success(const std::string& val) {
    success = val;
  }

  bool operator == (const ProxyServer_echo_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const ProxyServer_echo_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ProxyServer_echo_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _ProxyServer_echo_presult__isset {
  _ProxyServer_echo_presult__isset() : success(false) {}
  bool success;
} _ProxyServer_echo_presult__isset;

class ProxyServer_echo_presult {
 public:


  virtual ~ProxyServer_echo_presult() throw() {}

  std::string* success;

  _ProxyServer_echo_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class ProxyServerClient : virtual public ProxyServerIf {
 public:
  ProxyServerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  ProxyServerClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  int32_t ping();
  void send_ping();
  int32_t recv_ping();
  void echo(std::string& _return, const std::string& str);
  void send_echo(const std::string& str);
  void recv_echo(std::string& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class ProxyServerProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<ProxyServerIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (ProxyServerProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_ping(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_echo(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  ProxyServerProcessor(boost::shared_ptr<ProxyServerIf> iface) :
    iface_(iface) {
    processMap_["ping"] = &ProxyServerProcessor::process_ping;
    processMap_["echo"] = &ProxyServerProcessor::process_echo;
  }

  virtual ~ProxyServerProcessor() {}
};

class ProxyServerProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  ProxyServerProcessorFactory(const ::boost::shared_ptr< ProxyServerIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< ProxyServerIfFactory > handlerFactory_;
};

class ProxyServerMultiface : virtual public ProxyServerIf {
 public:
  ProxyServerMultiface(std::vector<boost::shared_ptr<ProxyServerIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~ProxyServerMultiface() {}
 protected:
  std::vector<boost::shared_ptr<ProxyServerIf> > ifaces_;
  ProxyServerMultiface() {}
  void add(boost::shared_ptr<ProxyServerIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  int32_t ping() {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->ping();
    }
    return ifaces_[i]->ping();
  }

  void echo(std::string& _return, const std::string& str) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->echo(_return, str);
    }
    ifaces_[i]->echo(_return, str);
    return;
  }

};

} // namespace

#endif
