/**
 * Autogenerated by Thrift Compiler (0.9.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef cpp_linux_TYPES_H
#define cpp_linux_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace azure { namespace storage { namespace cpp_linux {

struct MatchInformation {
  enum type {
    OnlyOnServer = 1,
    OnlyInKeys = 2,
    DeletedOnClient = 3,
    Match = 4
  };
};

extern const std::map<int, const char*> _MatchInformation_VALUES_TO_NAMES;

class ChunkInfo;

class StreamDataLayout;

typedef struct _ChunkInfo__isset {
  _ChunkInfo__isset() : OffSet(false), Length(false), Version(false), IsNullDataWritten(false), IsCorrupted(false) {}
  bool OffSet :1;
  bool Length :1;
  bool Version :1;
  bool IsNullDataWritten :1;
  bool IsCorrupted :1;
} _ChunkInfo__isset;

class ChunkInfo {
 public:

  static const char* ascii_fingerprint; // = "2D1F7C9D7EF060322343EC2AB2852351";
  static const uint8_t binary_fingerprint[16]; // = {0x2D,0x1F,0x7C,0x9D,0x7E,0xF0,0x60,0x32,0x23,0x43,0xEC,0x2A,0xB2,0x85,0x23,0x51};

  ChunkInfo(const ChunkInfo&);
  ChunkInfo& operator=(const ChunkInfo&);
  ChunkInfo() : OffSet(0), Length(0), Version(0), IsNullDataWritten(0), IsCorrupted(0) {
  }

  virtual ~ChunkInfo() throw();
  int64_t OffSet;
  int32_t Length;
  int8_t Version;
  bool IsNullDataWritten;
  bool IsCorrupted;

  _ChunkInfo__isset __isset;

  void __set_OffSet(const int64_t val);

  void __set_Length(const int32_t val);

  void __set_Version(const int8_t val);

  void __set_IsNullDataWritten(const bool val);

  void __set_IsCorrupted(const bool val);

  bool operator == (const ChunkInfo & rhs) const
  {
    if (!(OffSet == rhs.OffSet))
      return false;
    if (!(Length == rhs.Length))
      return false;
    if (!(Version == rhs.Version))
      return false;
    if (!(IsNullDataWritten == rhs.IsNullDataWritten))
      return false;
    if (!(IsCorrupted == rhs.IsCorrupted))
      return false;
    return true;
  }
  bool operator != (const ChunkInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ChunkInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const ChunkInfo& obj);
};

void swap(ChunkInfo &a, ChunkInfo &b);

typedef struct _StreamDataLayout__isset {
  _StreamDataLayout__isset() : Chunks(false), Length(false) {}
  bool Chunks :1;
  bool Length :1;
} _StreamDataLayout__isset;

class StreamDataLayout {
 public:

  static const char* ascii_fingerprint; // = "80E1C3D0F6200FD3585FF05B5D9711A9";
  static const uint8_t binary_fingerprint[16]; // = {0x80,0xE1,0xC3,0xD0,0xF6,0x20,0x0F,0xD3,0x58,0x5F,0xF0,0x5B,0x5D,0x97,0x11,0xA9};

  StreamDataLayout(const StreamDataLayout&);
  StreamDataLayout& operator=(const StreamDataLayout&);
  StreamDataLayout() : Length(0) {
  }

  virtual ~StreamDataLayout() throw();
  std::vector<ChunkInfo>  Chunks;
  int64_t Length;

  _StreamDataLayout__isset __isset;

  void __set_Chunks(const std::vector<ChunkInfo> & val);

  void __set_Length(const int64_t val);

  bool operator == (const StreamDataLayout & rhs) const
  {
    if (!(Chunks == rhs.Chunks))
      return false;
    if (!(Length == rhs.Length))
      return false;
    return true;
  }
  bool operator != (const StreamDataLayout &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const StreamDataLayout & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  friend std::ostream& operator<<(std::ostream& out, const StreamDataLayout& obj);
};

void swap(StreamDataLayout &a, StreamDataLayout &b);

}}} // namespace

#endif
