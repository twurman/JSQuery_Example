// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

//generated files
#include "gen-cpp/IPAService.h"
#include "gen-cpp/SchedulerService.h"
#include "gen-cpp/types_types.h"

//thrift dependencies 
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/THttpServer.h>
#include <thrift/transport/THttpClient.h>
#include <thrift/transport/THttpTransport.h>
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/TToString.h>
#include <thrift/transport/TTransportException.h>
#include <thrift/transport/TSocket.h>

//std library
#include <iostream>

//boost threading libraries
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using boost::shared_ptr;

// define the constant
#define THREAD_WORKS 16

class IPAServiceHandler : virtual public IPAServiceIf {
 public:
  IPAServiceHandler() {
    // Your initialization goes here
  }

  void submitQuery(std::string& _return, const QuerySpec& query) {
    for(int i = 0; i < query.content.size(); i++) {
      cout << "Type: " << query.content[i].type << endl;
      cout << "Data: ";
      for(int j = 0; j < query.content[i].data.size(); j++) {
        cout << query.content[i].data[j] << ", ";
      }
      cout << endl;

      cout << "Tags: ";
      for(int j = 0; j < query.content[i].data.size(); j++) {
        cout << query.content[i].tags[j] << ", ";
      }
      cout << endl;
    }
    _return = "Done";
  }

};

int main(int argc, char **argv){
  int port = 9091;
  if (argv[1]) {
    port = atoi(argv[1]);
  } else {
    cout << "Using default port for service..." << endl;
  }

  shared_ptr<IPAServiceHandler> handler(new IPAServiceHandler());
  shared_ptr<TProcessor> processor(new IPAServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new THttpServerTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TJSONProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);

  cout << "Starting the query conversion server on port " << port << "... ";
  boost::thread *serverThread = new boost::thread(boost::bind(&TSimpleServer::serve, &server));
  cout << "Done" << endl;
  

  int cc_port = 4444;
  if (argv[2]) {
    cc_port = atoi(argv[2]);
  } else {
    cout << "Using default port for sudo cc..." << endl;
  }
  cout << "Registering with sudo cc at port " << cc_port << "... " << endl;
  boost::shared_ptr<TTransport> cmdtransport(new THttpClient("localhost", cc_port, "/"));
  boost::shared_ptr<TProtocol> cmdprotocol(new TJSONProtocol(cmdtransport));
  SchedulerServiceClient cmdclient(cmdprotocol);
  cmdtransport->open();
  
  THostPort endpoint;
  endpoint.ip = "clarity04.eecs.umich.edu";
  endpoint.port = port;
  
  RegMessage message;
  message.app_name = "Sirius";
  message.endpoint = endpoint;
  try {
    cmdclient.registerBackend(message);
  } catch(TTransportException exc) {
    cout << exc.what() << endl;
  }
  
  cout << "Done" << endl;

  serverThread->join();
  cmdtransport->close();
  return 0;
}
