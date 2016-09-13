/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef FileShareService_H
#define FileShareService_H

#include <thrift/TDispatchProcessor.h>
#include "cpp_linux_types.h"

namespace azure { namespace storage { namespace cpp_linux {

class FileShareServiceIf {
 public:
  virtual ~FileShareServiceIf() {}
  virtual void MapFileShare(LinuxFileResponse& _return, const std::string& smbShareAddress, const std::string& username, const std::string& password, const std::string& mountPoint) = 0;
  virtual void UnmapFileShare(LinuxFileResponse& _return, const std::string& mountPoint) = 0;
};

class FileShareServiceIfFactory {
 public:
  typedef FileShareServiceIf Handler;

  virtual ~FileShareServiceIfFactory() {}

  virtual FileShareServiceIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(FileShareServiceIf* /* handler */) = 0;
};

class FileShareServiceIfSingletonFactory : virtual public FileShareServiceIfFactory {
 public:
  FileShareServiceIfSingletonFactory(const boost::shared_ptr<FileShareServiceIf>& iface) : iface_(iface) {}
  virtual ~FileShareServiceIfSingletonFactory() {}

  virtual FileShareServiceIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(FileShareServiceIf* /* handler */) {}

 protected:
  boost::shared_ptr<FileShareServiceIf> iface_;
};

class FileShareServiceNull : virtual public FileShareServiceIf {
 public:
  virtual ~FileShareServiceNull() {}
  void MapFileShare(LinuxFileResponse& /* _return */, const std::string& /* smbShareAddress */, const std::string& /* username */, const std::string& /* password */, const std::string& /* mountPoint */) {
    return;
  }
  void UnmapFileShare(LinuxFileResponse& /* _return */, const std::string& /* mountPoint */) {
    return;
  }
};

typedef struct _FileShareService_MapFileShare_args__isset {
  _FileShareService_MapFileShare_args__isset() : smbShareAddress(false), username(false), password(false), mountPoint(false) {}
  bool smbShareAddress :1;
  bool username :1;
  bool password :1;
  bool mountPoint :1;
} _FileShareService_MapFileShare_args__isset;

class FileShareService_MapFileShare_args {
 public:

  static const char* ascii_fingerprint; // = "C93D890311F28844166CF6E571EB3AC2";
  static const uint8_t binary_fingerprint[16]; // = {0xC9,0x3D,0x89,0x03,0x11,0xF2,0x88,0x44,0x16,0x6C,0xF6,0xE5,0x71,0xEB,0x3A,0xC2};

  FileShareService_MapFileShare_args(const FileShareService_MapFileShare_args&);
  FileShareService_MapFileShare_args& operator=(const FileShareService_MapFileShare_args&);
  FileShareService_MapFileShare_args() : smbShareAddress(), username(), password(), mountPoint() {
  }

  virtual ~FileShareService_MapFileShare_args() throw();
  std::string smbShareAddress;
  std::string username;
  std::string password;
  std::string mountPoint;

  _FileShareService_MapFileShare_args__isset __isset;

  void __set_smbShareAddress(const std::string& val);

  void __set_username(const std::string& val);

  void __set_password(const std::string& val);

  void __set_mountPoint(const std::string& val);

  bool operator == (const FileShareService_MapFileShare_args & rhs) const
  {
    if (!(smbShareAddress == rhs.smbShareAddress))
      return false;
    if (!(username == rhs.username))
      return false;
    if (!(password == rhs.password))
      return false;
    if (!(mountPoint == rhs.mountPoint))
      return false;
    return true;
  }
  bool operator != (const FileShareService_MapFileShare_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileShareService_MapFileShare_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const FileShareService_MapFileShare_args& obj);
};


class FileShareService_MapFileShare_pargs {
 public:

  static const char* ascii_fingerprint; // = "C93D890311F28844166CF6E571EB3AC2";
  static const uint8_t binary_fingerprint[16]; // = {0xC9,0x3D,0x89,0x03,0x11,0xF2,0x88,0x44,0x16,0x6C,0xF6,0xE5,0x71,0xEB,0x3A,0xC2};


  virtual ~FileShareService_MapFileShare_pargs() throw();
  const std::string* smbShareAddress;
  const std::string* username;
  const std::string* password;
  const std::string* mountPoint;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const FileShareService_MapFileShare_pargs& obj);
};

typedef struct _FileShareService_MapFileShare_result__isset {
  _FileShareService_MapFileShare_result__isset() : success(false), linuxFileException(false) {}
  bool success :1;
  bool linuxFileException :1;
} _FileShareService_MapFileShare_result__isset;

class FileShareService_MapFileShare_result {
 public:

  static const char* ascii_fingerprint; // = "8C54A0F98807EFF15041206ACA731580";
  static const uint8_t binary_fingerprint[16]; // = {0x8C,0x54,0xA0,0xF9,0x88,0x07,0xEF,0xF1,0x50,0x41,0x20,0x6A,0xCA,0x73,0x15,0x80};

  FileShareService_MapFileShare_result(const FileShareService_MapFileShare_result&);
  FileShareService_MapFileShare_result& operator=(const FileShareService_MapFileShare_result&);
  FileShareService_MapFileShare_result() {
  }

  virtual ~FileShareService_MapFileShare_result() throw();
  LinuxFileResponse success;
  LinuxFileException linuxFileException;

  _FileShareService_MapFileShare_result__isset __isset;

  void __set_success(const LinuxFileResponse& val);

  void __set_linuxFileException(const LinuxFileException& val);

  bool operator == (const FileShareService_MapFileShare_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(linuxFileException == rhs.linuxFileException))
      return false;
    return true;
  }
  bool operator != (const FileShareService_MapFileShare_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileShareService_MapFileShare_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const FileShareService_MapFileShare_result& obj);
};

typedef struct _FileShareService_MapFileShare_presult__isset {
  _FileShareService_MapFileShare_presult__isset() : success(false), linuxFileException(false) {}
  bool success :1;
  bool linuxFileException :1;
} _FileShareService_MapFileShare_presult__isset;

class FileShareService_MapFileShare_presult {
 public:

  static const char* ascii_fingerprint; // = "8C54A0F98807EFF15041206ACA731580";
  static const uint8_t binary_fingerprint[16]; // = {0x8C,0x54,0xA0,0xF9,0x88,0x07,0xEF,0xF1,0x50,0x41,0x20,0x6A,0xCA,0x73,0x15,0x80};


  virtual ~FileShareService_MapFileShare_presult() throw();
  LinuxFileResponse* success;
  LinuxFileException linuxFileException;

  _FileShareService_MapFileShare_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const FileShareService_MapFileShare_presult& obj);
};

typedef struct _FileShareService_UnmapFileShare_args__isset {
  _FileShareService_UnmapFileShare_args__isset() : mountPoint(false) {}
  bool mountPoint :1;
} _FileShareService_UnmapFileShare_args__isset;

class FileShareService_UnmapFileShare_args {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  FileShareService_UnmapFileShare_args(const FileShareService_UnmapFileShare_args&);
  FileShareService_UnmapFileShare_args& operator=(const FileShareService_UnmapFileShare_args&);
  FileShareService_UnmapFileShare_args() : mountPoint() {
  }

  virtual ~FileShareService_UnmapFileShare_args() throw();
  std::string mountPoint;

  _FileShareService_UnmapFileShare_args__isset __isset;

  void __set_mountPoint(const std::string& val);

  bool operator == (const FileShareService_UnmapFileShare_args & rhs) const
  {
    if (!(mountPoint == rhs.mountPoint))
      return false;
    return true;
  }
  bool operator != (const FileShareService_UnmapFileShare_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileShareService_UnmapFileShare_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const FileShareService_UnmapFileShare_args& obj);
};


class FileShareService_UnmapFileShare_pargs {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};


  virtual ~FileShareService_UnmapFileShare_pargs() throw();
  const std::string* mountPoint;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const FileShareService_UnmapFileShare_pargs& obj);
};

typedef struct _FileShareService_UnmapFileShare_result__isset {
  _FileShareService_UnmapFileShare_result__isset() : success(false), linuxFileException(false) {}
  bool success :1;
  bool linuxFileException :1;
} _FileShareService_UnmapFileShare_result__isset;

class FileShareService_UnmapFileShare_result {
 public:

  static const char* ascii_fingerprint; // = "8C54A0F98807EFF15041206ACA731580";
  static const uint8_t binary_fingerprint[16]; // = {0x8C,0x54,0xA0,0xF9,0x88,0x07,0xEF,0xF1,0x50,0x41,0x20,0x6A,0xCA,0x73,0x15,0x80};

  FileShareService_UnmapFileShare_result(const FileShareService_UnmapFileShare_result&);
  FileShareService_UnmapFileShare_result& operator=(const FileShareService_UnmapFileShare_result&);
  FileShareService_UnmapFileShare_result() {
  }

  virtual ~FileShareService_UnmapFileShare_result() throw();
  LinuxFileResponse success;
  LinuxFileException linuxFileException;

  _FileShareService_UnmapFileShare_result__isset __isset;

  void __set_success(const LinuxFileResponse& val);

  void __set_linuxFileException(const LinuxFileException& val);

  bool operator == (const FileShareService_UnmapFileShare_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(linuxFileException == rhs.linuxFileException))
      return false;
    return true;
  }
  bool operator != (const FileShareService_UnmapFileShare_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const FileShareService_UnmapFileShare_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const FileShareService_UnmapFileShare_result& obj);
};

typedef struct _FileShareService_UnmapFileShare_presult__isset {
  _FileShareService_UnmapFileShare_presult__isset() : success(false), linuxFileException(false) {}
  bool success :1;
  bool linuxFileException :1;
} _FileShareService_UnmapFileShare_presult__isset;

class FileShareService_UnmapFileShare_presult {
 public:

  static const char* ascii_fingerprint; // = "8C54A0F98807EFF15041206ACA731580";
  static const uint8_t binary_fingerprint[16]; // = {0x8C,0x54,0xA0,0xF9,0x88,0x07,0xEF,0xF1,0x50,0x41,0x20,0x6A,0xCA,0x73,0x15,0x80};


  virtual ~FileShareService_UnmapFileShare_presult() throw();
  LinuxFileResponse* success;
  LinuxFileException linuxFileException;

  _FileShareService_UnmapFileShare_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

  friend std::ostream& operator<<(std::ostream& out, const FileShareService_UnmapFileShare_presult& obj);
};

class FileShareServiceClient : virtual public FileShareServiceIf {
 public:
  FileShareServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  FileShareServiceClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void MapFileShare(LinuxFileResponse& _return, const std::string& smbShareAddress, const std::string& username, const std::string& password, const std::string& mountPoint);
  void send_MapFileShare(const std::string& smbShareAddress, const std::string& username, const std::string& password, const std::string& mountPoint);
  void recv_MapFileShare(LinuxFileResponse& _return);
  void UnmapFileShare(LinuxFileResponse& _return, const std::string& mountPoint);
  void send_UnmapFileShare(const std::string& mountPoint);
  void recv_UnmapFileShare(LinuxFileResponse& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class FileShareServiceProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<FileShareServiceIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (FileShareServiceProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_MapFileShare(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_UnmapFileShare(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  FileShareServiceProcessor(boost::shared_ptr<FileShareServiceIf> iface) :
    iface_(iface) {
    processMap_["MapFileShare"] = &FileShareServiceProcessor::process_MapFileShare;
    processMap_["UnmapFileShare"] = &FileShareServiceProcessor::process_UnmapFileShare;
  }

  virtual ~FileShareServiceProcessor() {}
};

class FileShareServiceProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  FileShareServiceProcessorFactory(const ::boost::shared_ptr< FileShareServiceIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< FileShareServiceIfFactory > handlerFactory_;
};

class FileShareServiceMultiface : virtual public FileShareServiceIf {
 public:
  FileShareServiceMultiface(std::vector<boost::shared_ptr<FileShareServiceIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~FileShareServiceMultiface() {}
 protected:
  std::vector<boost::shared_ptr<FileShareServiceIf> > ifaces_;
  FileShareServiceMultiface() {}
  void add(boost::shared_ptr<FileShareServiceIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void MapFileShare(LinuxFileResponse& _return, const std::string& smbShareAddress, const std::string& username, const std::string& password, const std::string& mountPoint) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->MapFileShare(_return, smbShareAddress, username, password, mountPoint);
    }
    ifaces_[i]->MapFileShare(_return, smbShareAddress, username, password, mountPoint);
    return;
  }

  void UnmapFileShare(LinuxFileResponse& _return, const std::string& mountPoint) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->UnmapFileShare(_return, mountPoint);
    }
    ifaces_[i]->UnmapFileShare(_return, mountPoint);
    return;
  }

};

}}} // namespace

#endif
