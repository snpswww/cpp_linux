// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "XSMBService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::azure::storage::cpp_linux;

class XSMBServiceHandler : virtual public XSMBServiceIf {
 public:
  XSMBServiceHandler() {
    // Your initialization goes here
  }

  void CreateDirectory(LinuxFileResponse& _return, const std::string& dirPath) {
    // Your implementation goes here
    printf("CreateDirectory\n");
  }

  void DeleteDirectory(LinuxFileResponse& _return, const std::string& dirPath, const bool isRecursive) {
    // Your implementation goes here
    printf("DeleteDirectory\n");
  }

  void CreateFile(LinuxFileResponse& _return, const std::string& filePath, const int64_t fileSize, const bool noBuffering) {
    // Your implementation goes here
    printf("CreateFile\n");
  }

  void DeleteFile(LinuxFileResponse& _return, const std::string& filePath) {
    // Your implementation goes here
    printf("DeleteFile\n");
  }

  void ReadFile(LinuxFileResponse& _return, const std::string& filePath, const int64_t offset, const int64_t count) {
    // Your implementation goes here
    printf("ReadFile\n");
  }

  void WriteFile(LinuxFileResponse& _return, const std::string& filePath, const int64_t offset, const std::string& buffer, const int64_t count) {
    // Your implementation goes here
    printf("WriteFile\n");
  }

  void ListFiles(LinuxFileResponse& _return, const std::string& dirPath, const bool isRecursive, const std::map<std::string, MatchInformation::type> & files, const std::map<std::string, MatchInformation::type> & dirs) {
    // Your implementation goes here
    printf("ListFiles\n");
  }

  void GetFileLength(LinuxFileResponse& _return, const std::string& filePath) {
    // Your implementation goes here
    printf("GetFileLength\n");
  }

  void SetFileLength(LinuxFileResponse& _return, const std::string& filePath, const int64_t fileLength) {
    // Your implementation goes here
    printf("SetFileLength\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<XSMBServiceHandler> handler(new XSMBServiceHandler());
  shared_ptr<TProcessor> processor(new XSMBServiceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

